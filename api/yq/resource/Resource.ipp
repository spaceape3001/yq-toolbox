////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Resource.hpp"
#include "ResourceDriverAPI.hpp"
#include "ResourceLogging.hpp"
#include "ResourceMetaWriter.hpp"

#include <yq/tags.hpp>
#include <yq/file/FileUtils.hpp>
#include <yq/text/match.hpp>
#include <yq/text/transform.hpp>
#include <yq/text/vsplit.hpp>
#include <yq/util/Iterable.hpp>

YQ_OBJECT_IMPLEMENT(yq::Resource)

namespace yq {
    namespace errors {
        using filepath_existing             = error_db::entry<"Filepath already exists">;
        using invalid_collision_strategy    = error_db::entry<"File collision strategy is invalid">;
        using loading_exception             = error_db::entry<"Exception thrown during loading">;
        using no_file_extension             = error_db::entry<"No file extension provided to file">;
        using no_savers_defined             = error_db::entry<"Resource class has NO saving functions defined">;
        using no_savers_applicable          = error_db::entry<"No file savers defined for given output">;
        using saving_exception              = error_db::entry<"Exception thrown during saving">;
    }

////////////////////////////////////////////////////////////////////////////////

    ResourceMeta::ResourceMeta(std::string_view zName, ObjectMeta& base, const std::source_location& sl) :
        ObjectMeta(zName, base, sl)
    {
        set(Flag::RESOURCE);
        Resource::repo().resources.push_back(this);
    }

    void Resource::init_meta()
    {
        auto w = writer<Resource>();
        w.description("Resource (ie texture, mesh, shader, etc)");
        w.property("url", &Resource::m_url).tag({kTag_Save});
        w.abstract();
    }

////////////////////////////////////////////////////////////////////////////////

    ResourceInfoCPtr            Resource::_info(const ResourceMeta&am, ResourceInfoAPI&api)
    {
        static const Repo& _r   = repo();
        return {};  // TODO
    }
    
    ResourceCPtr                Resource::_load(const ResourceMeta&am, ResourceLoadAPI&api)
    {
        static Cache& _c        = cache();
        
        if(api.m_options.load != Tristate::YES){
            ResourceCPtr   ap  = _c.lookup(api.m_url);
            if(ap)
                return ap;
        }
        
        ResourceCPtr       ret;
        if(!api.m_url.fragment.empty()){
            ret = _load_fragment(am, api);
        } else if(is_similar(api.m_url.scheme, "file")){
            ret = _load_file(am, api);
        } else {
        }

        // right now, non files aren't supported... (TODO)
        if(!ret){
            resourceWarning << "Unable to load (" << to_string(api.m_url) << "): no suitable libraries/loaders loaded it.";
            return {};
        }
        
        Resource* ass      = const_cast<Resource*>(ret.ptr());
        ass -> m_url    = api.m_url;

        if(ResourceLibrary* lib = dynamic_cast<ResourceLibrary*>(ass)){
            for(auto& itr : lib->m_resources){
                if(!itr.second)
                    continue;
                    
                Resource* ass2             = const_cast<Resource*>(itr.second.ptr());
                ass2->m_url             = api.m_url;
                ass2->m_url.fragment    = std::string(itr.first);
                if(api.m_options.cache != Tristate::NO){
                    ass2 -> m_readonly   = true;
                    _c.inject(itr.second);
                }
            }
        }

        if(api.m_options.cache != Tristate::NO){
            ass -> m_readonly    = true;
            _c.inject(ret);
        }
            
        return ret;
    }

    ResourceCPtr                Resource::_load_file(const ResourceMeta&am, ResourceLoadAPI&api)
    {
        static const Repo& _r   = repo();
        std::string_view    ext = file_extension(api.m_url.path);
        if(ext.empty()){
            resourceWarning << "Unable to load (" << to_string(api.m_url) << "): no file extension";
            return {};
        }

        ResourceCPtr ret;

        for(auto& itr : as_iterable(_r.loaders.equal_range(std::string(ext)))){
            const ResourceLoader* ld    = itr.second;
            if(!ld)
                continue;
            if(!ld->resource().is_base_or_this(am))    // (unrelated) so total skip
                continue;
                
            std::error_code ec;
            try {
                ret = ld -> load(api.m_url, api);
            } 
            catch(std::error_code ex)
            {
                ec  = ex;
            }
            #ifdef NDEBUG
            catch(...)
            {
                ec  = errors::loading_exception();
            }
            #endif
            
            if(ec != std::error_code()){
                ret = {};
                resourceWarning << "Unable to load (" << to_string(api.m_url) << "): " << ec.message();
                continue;
            }
            
            if(ret)
                break;
        }

        return ret;
    }
    
    ResourceCPtr                Resource::_load_fragment(const ResourceMeta&am, ResourceLoadAPI&api)
    {
        static const ResourceLoadOptions   s_default;
        
        ResourceLoadAPI    api2( api.m_options.library ? *api.m_options.library : s_default);
        api2.m_url          = api.m_url;
        api2.m_url.fragment = {};       // zap the fragment
        
        ResourceCPtr   libAss   = _load(meta<ResourceLibrary>(), api2);
        if(!libAss)
            return {};
        
        ResourceLibraryCPtr    asslib  = dynamic_cast<const ResourceLibrary*>(libAss.ptr());
        if(!asslib) [[unlikely]]
            return {};
            
        ResourceCPtr ret = asslib -> resource(api.m_url.fragment);
        
        if(!ret){
            resourceWarning << "Unable to load (" << to_string(api.m_url) << "): no suitable libraries/loaders loaded it.";
            return {};
        }
        
        if(!ret->metaInfo().is_derived_or_this(am)){
            resourceWarning << "Unable to load (" << to_string(api.m_url) << "): not a suitable resource type.";
            return {};
        }
        
        return ret;
    }
    
    std::error_code          Resource::_save(const Resource& resource, ResourceSaveAPI&api)
    {
        if(!api.m_url.fragment.empty()){
            resourceWarning << "Resource saving to '" << to_string(api.m_url) << "' does not support saving into libraries.";
            return errors::todo();
        }
        
        if(!is_similar(api.m_url.scheme, "file")){
            resourceWarning << "Resource saving to '" << to_string(api.m_url) << "' does not support saving to non-files.";
            return errors::todo();
        }
        
        return _save_file(resource, api);
    }

    std::error_code          Resource::_save_file(const Resource& resource, ResourceSaveAPI& api)
    {
        static Repo& _r     = repo();
        static Cache& _c    = cache();
        
        const ResourceMeta&    am  = resource.metaInfo();

        std::string_view    ext = file_extension(api.m_url.path);
        if(ext.empty()){
            return errors::no_file_extension();
        }

        Url                     orig        = api.m_url;
        bool                    existing    = file_exists(api.m_url.path.c_str());
        bool                    backup      = false;

        if(existing){
            switch(api.m_options.collision){
            case FileCollisionStrategy::Abort:
                return errors::filepath_existing();
            case FileCollisionStrategy::Backup:
                backup  = true;
                // fall through is deliberate (annotate to get rid of warnings)
            case FileCollisionStrategy::Overwrite:
                api.m_url.path += "~tmp";
                break;
            default:
                return errors::invalid_collision_strategy();
            }
        }

        bool        saved   = false;
        for(auto& itr : as_iterable(_r.savers.equal_range(std::string(ext)))){
            const ResourceSaver* sv = itr.second;
            if(!sv)
                continue;
            if(!sv->resource().is_base_or_this(am))
                continue;
                
            std::error_code ec;
            try {
                ec = sv -> save(resource, api.m_url, api);
            }
            catch(const std::error_code& ec2){
                ec  = ec2;
            }
            #ifndef NDEBUG
            catch(...)
            {
                ec  = errors::saving_exception();
            }
            #endif

            if(ec == std::error_code()){
                resourceInfo << "Resource saved '" << to_string(api.m_url) << "'";
                saved = true;
                break;
            }

            resourceWarning << "Resource unable to save to '" << to_string(api.m_url) << "': " << ec.message();
        }
        
        if(!saved)
            return errors::no_savers_applicable(); 
            
        
        if(existing){
            if(backup){
                file_backup(orig.path.c_str());
            }
            rename(api.m_url.path.c_str(), orig.path.c_str());
        }

        if(api.m_options.set_name && !resource.m_readonly && (resource.m_url != orig) && !_c.contains(resource.id())){
            const_cast<Resource&>(resource).m_url   = orig;
        }

        return {};
    }

    void Resource::add_infoer(ResourceInfoer*d) 
    {
        if(Meta::thread_safe_write()){
            repo().inject(d);
        } else if(d)
            delete d;
    }
    
    void Resource::add_loader(ResourceLoader*d)
    {
        if(Meta::thread_safe_write()){
            repo().inject(d);
        } else {
            delete d;
        }
    }

    void    Resource::add_library(const ResourceLibraryCPtr& alp)
    {
        if(!alp)
            return;
        if(!Meta::thread_safe_write())
            return ;
        repo().search.push_back(alp);
    }
    
    void    Resource::add_path(const std::filesystem::path& fp)
    {
        if(!Meta::thread_safe_write())
            return ;
        if(has_path(fp))
            return ;
        repo().inject(fp);
    }
        
    void    Resource::add_paths(std::string_view dd)
    {
        vsplit(dd, ';', [&](std::string_view x){
            add_path(std::filesystem::path(trimmed(x)));
        });
    }

    void    Resource::add_saver(ResourceSaver*d)
    {
        if(Meta::thread_safe_write()){
            repo().inject(d);
        } else if(d)
            delete d;
    }

    std::vector<std::filesystem::path>   Resource::all_paths()
    {
        std::vector<std::filesystem::path> ret;
        for(auto& sp : repo().search){
            if(auto p = std::get_if<std::filesystem::path>(&sp)){
                ret.push_back(*p);
            }
        }
        return ret;
    }


    ResourceInfoCPtr    Resource::resource_info(std::string_view spec, const ResourceInfoOptions& options)
    {
        return resource_info(meta<Resource>(), spec, options);
    }
    
    ResourceInfoCPtr    Resource::resource_info(const ResourceMeta&am, std::string_view spec, const ResourceInfoOptions& options)
    {
        ResourceInfoAPI    api(options);
        api.m_url       = resolve(spec);
        api.m_spec      = spec;
        return _info(am, api);
    }

    ResourceInfoCPtr    Resource::resource_info(const UrlView& url, const ResourceInfoOptions& options)
    {
        return resource_info(meta<Resource>(), url, options);
    }

    ResourceInfoCPtr    Resource::resource_info(const ResourceMeta& am, const UrlView& url, const ResourceInfoOptions& options)
    {
        ResourceInfoAPI    api(options);
        api.m_url   = copy(url);
        api.m_spec  = to_string(url);
        return _info(am, api);
    }
    
    ResourceInfoCPtr    Resource::resource_info(const std::filesystem::path& fp, const ResourceInfoOptions& options)
    {
        return resource_info(meta<Resource>(), fp, options);
    }

    ResourceInfoCPtr    Resource::resource_info(const ResourceMeta&am, const std::filesystem::path&fp, const ResourceInfoOptions& options)
    {
        ResourceInfoAPI    api(options);
        api.m_url.scheme    = "file";
        api.m_url.path      = fp.string();
        api.m_spec  = to_string(api.m_url);
        return _info(am, api);
    }

    ResourceInfoCPtr    Resource::resource_info(const std::filesystem::path&fp, std::string_view frag, const ResourceInfoOptions& options)
    {
        return resource_info(meta<Resource>(), fp, frag, options);
    }

    ResourceInfoCPtr    Resource::resource_info(const ResourceMeta&am, const std::filesystem::path& fp, std::string_view frag, const ResourceInfoOptions& options)
    {
        ResourceInfoAPI    api(options);
        api.m_url.scheme    = "file";
        api.m_url.path      = fp.string();
        api.m_url.fragment  = std::string(frag);
        api.m_spec  = to_string(api.m_url);
        return _info(am, api);
    }

    ResourceCPtr        Resource::resource_load(std::string_view spec, const ResourceLoadOptions& options)
    {
        return resource_load(meta<Resource>(), spec, options);
    }

    ResourceCPtr        Resource::resource_load(const ResourceMeta&am, std::string_view spec, const ResourceLoadOptions& options)
    {
        ResourceLoadAPI        api(options);
        api.m_url       = resolve(spec);
        api.m_spec      = spec;
        return _load(am, api);
    }

    ResourceCPtr        Resource::resource_load(const UrlView&url, const ResourceLoadOptions& options)
    {
        return resource_load(meta<Resource>(), url, options);
    }

    ResourceCPtr        Resource::resource_load(const ResourceMeta&am, const UrlView&url, const ResourceLoadOptions& options)
    {
        ResourceLoadAPI    api(options);
        api.m_url   = copy(url);
        api.m_spec  = to_string(url);
        return _load(am, api);
    }
        
    ResourceCPtr        Resource::resource_load(const std::filesystem::path&fp, const ResourceLoadOptions& options)
    {
        return resource_load(meta<Resource>(), fp, options);
    }

    ResourceCPtr        Resource::resource_load(const ResourceMeta&am, const std::filesystem::path& fp, const ResourceLoadOptions& options)
    {
        ResourceLoadAPI    api(options);
        api.m_url.scheme    = "file";
        api.m_url.path      = fp.string();
        api.m_spec  = to_string(api.m_url);
        return _load(am, api);
    }
    
    ResourceCPtr        Resource::resource_load(const std::filesystem::path& fp, std::string_view frag, const ResourceLoadOptions& options)
    {
        return resource_load(meta<Resource>(), fp, frag, options);
    }

    ResourceCPtr        Resource::resource_load(const ResourceMeta&am, const std::filesystem::path&fp, std::string_view frag, const ResourceLoadOptions& options)
    {
        ResourceLoadAPI    api(options);
        api.m_url.scheme    = "file";
        api.m_url.path      = fp.string();
        api.m_url.fragment  = std::string(frag);
        api.m_spec  = to_string(api.m_url);
        return _load(am, api);
    }
        
    Url  Resource::resolve(std::string_view u)
    {
        u = trimmed(u);
        if(u.empty())
            return {};
    
        Url         ret;
        auto    colon  = u.find_first_of(':');

        if(colon != std::string_view::npos){
            auto uv = to_url_view(u);
            if(!uv.good)
                return {};
            if(!is_similar(ret.scheme, "file"))
                return copy(uv.value);
            ret     = copy(uv.value);
        } else {
            auto hash   = u.find_first_of('#');
            if(hash != std::string_view::npos){
                ret.path        = std::string(u.substr(0, hash));
                ret.fragment    = std::string(u.substr(hash+1));
            } else
                ret.path        = u;
            ret.scheme  = "file";
        }
        
        if(ret.path.empty())
            return {};
        
        if(ret.path[0] != '/'){
            for(auto& sp : repo().search){
                if(auto p = std::get_if<std::filesystem::path>(&sp)){
                    std::filesystem::path   fp  = *p / ret.path;
                    if(file_exists(fp)){
                        ret.path    = fp.string();
                        return ret;
                    }
                }
                
                if(auto p = std::get_if<ResourceLibraryCPtr>(&sp)){
                    if(!ret.fragment.empty())  // not doing multple libraries deep....
                        continue;
                    if((*p) && (*p)->contains(ret.path)){
                        Url u2   = (*p) -> url();
                        u2.fragment  = ret.path;
                        return u2;
                    }
                }
            }
        }
        
        return ret;
    }

    bool             Resource::has_path(const std::filesystem::path& fp)
    {
        for(auto& sp : repo().search){
            if(auto p = std::get_if<std::filesystem::path>(&sp)){
                if(*p == fp)
                    return true;
            }
        }
        return false;
    }


/////////////////

    Resource::Resource()
    {
    }

    Resource::~Resource()
    {
    }

    std::string_view Resource::extension() const
    {
        if(!m_url.fragment.empty())
            return file_extension(m_url.fragment);
        if(!m_url.path.empty())
            return file_extension(m_url.path);
        return {};
    }

    std::filesystem::path   Resource::filepath() const
    {
        return std::filesystem::path(m_url.path);
    }

    void              Resource::inject()
    {
        m_readonly  = true;
        cache().inject(this);
    }

    std::error_code   Resource::save(const ResourceSaveOptions& options) const
    {
        ResourceSaveAPI    api(options);
        api.m_url      = m_url;
        return _save(*this, api);
    }

    std::error_code Resource::save_to(const std::filesystem::path&fp, const ResourceSaveOptions& options) const
    {
        ResourceSaveAPI    api(options);
        api.m_url.scheme    = "file";
        api.m_url.path      = fp.string();
        return _save(*this, api);
    }
    
    std::error_code Resource::save_to(const UrlView&url, const ResourceSaveOptions& options) const
    {
        ResourceSaveAPI    api(options);
        api.m_url      = copy(url);
        return _save(*this, api);
    }

    void Resource::set_url(const std::filesystem::path&fp) 
    {
        if(m_readonly)
            return;
        m_url.scheme    = "file";
        m_url.path = fp.string();
    }

    void Resource::set_url(const UrlView& url) 
    {
        if(m_readonly)
            return;
        m_url = copy(url);
    }

////////////////////////////////////////////////////////////////////////////////
}
