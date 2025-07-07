////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Asset.hpp"
#include "AssetMetaWriter.hpp"

#include <yq/tags.hpp>
#include <yq/file/FileUtils.hpp>
#include <yq/text/match.hpp>
#include <yq/text/transform.hpp>
#include <yq/text/vsplit.hpp>
#include <yq/util/Iterable.hpp>

YQ_OBJECT_IMPLEMENT(yq::Asset)
YQ_OBJECT_IMPLEMENT(yq::AssetInfo)

namespace yq {
    namespace errors {
        using filepath_existing             = error_db::entry<"Filepath already exists">;
        using invalid_collision_strategy    = error_db::entry<"File collision strategy is invalid">;
        using loading_exception             = error_db::entry<"Exception thrown during loading">;
        using no_file_extension             = error_db::entry<"No file extension provided to file">;
        using no_savers_defined             = error_db::entry<"Asset class has NO saving functions defined">;
        using no_savers_applicable          = error_db::entry<"No file savers defined for given output">;
        using saving_exception              = error_db::entry<"Exception thrown during saving">;
    }

////////////////////////////////////////////////////////////////////////////////

    AssetMeta::AssetMeta(std::string_view zName, ObjectMeta& base, const std::source_location& sl) :
        ObjectMeta(zName, base, sl)
    {
        set(Flag::ASSET);
        Asset::repo().assets.push_back(this);
    }

    void Asset::init_meta()
    {
        auto w = writer<Asset>();
        w.description("Asset (ie texture, mesh, shader, etc)");
        w.property("url", &Asset::m_url).tag({kTag_Save});
        w.abstract();
    }

////////////////////////////////////////////////////////////////////////////////

    AssetInfo::AssetInfo() = default;
    AssetInfo::~AssetInfo() = default;

    void AssetInfo::init_meta()
    {
        auto w = writer<AssetInfo>();
        w.description("Asset Information");
        w.property("url", &AssetInfo::m_url);
    }

////////////////////////////////////////////////////////////////////////////////

    AssetInfoCPtr            Asset::_info(const AssetMeta&am, AssetInfoAPI&api)
    {
        static const Repo& _r   = repo();
        return {};  // TODO
    }
    
    AssetCPtr                Asset::_load(const AssetMeta&am, AssetLoadAPI&api)
    {
        static Cache& _c        = cache();
        
        if(api.m_options.load != Tristate::YES){
            AssetCPtr   ap  = _c.lookup(api.m_url);
            if(ap)
                return ap;
        }
        
        AssetCPtr       ret;
        if(!api.m_url.fragment.empty()){
            ret = _load_fragment(am, api);
        } else if(is_similar(api.m_url.scheme, "file")){
            ret = _load_file(am, api);
        } else {
        }

        // right now, non files aren't supported... (TODO)
        if(!ret){
            assetWarning << "Unable to load (" << to_string(api.m_url) << "): no suitable libraries/loaders loaded it.";
            return {};
        }
        
        Asset* ass      = const_cast<Asset*>(ret.ptr());
        ass -> m_url    = api.m_url;

        if(AssetLibrary* lib = dynamic_cast<AssetLibrary*>(ass)){
            for(auto& itr : lib->m_assets){
                if(!itr.second)
                    continue;
                    
                Asset* ass2             = const_cast<Asset*>(itr.second.ptr());
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

    AssetCPtr                Asset::_load_file(const AssetMeta&am, AssetLoadAPI&api)
    {
        static const Repo& _r   = repo();
        std::string_view    ext = file_extension(api.m_url.path);
        if(ext.empty()){
            assetWarning << "Unable to load (" << to_string(api.m_url) << "): no file extension";
            return {};
        }
        
        AssetCPtr ret;
        
        for(auto& itr : as_iterable(_r.loaders.equal_range(ext))){
            const Loader* ld    = itr.second;
            if(!ld)
                continue;
            if(!ld->asset().is_base_or_this(am))    // (unrelated) so total skip
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
                assetWarning << "Unable to load (" << to_string(api.m_url) << "): " << ec.message();
                continue;
            }
            
            if(ret)
                break;
        }

        return ret;
    }
    
    AssetCPtr                Asset::_load_fragment(const AssetMeta&am, AssetLoadAPI&api)
    {
        static const AssetLoadOptions   s_default;
        
        AssetLoadAPI    api2( api.m_options.library ? *api.m_options.library : s_default);
        api2.m_url          = api.m_url;
        api2.m_url.fragment = {};       // zap the fragment
        
        AssetCPtr   libAss   = _load(meta<AssetLibrary>(), api2);
        if(!libAss)
            return {};
        
        AssetLibraryCPtr    asslib  = dynamic_cast<const AssetLibrary*>(libAss.ptr());
        if(!asslib) [[unlikely]]
            return {};
            
        AssetCPtr ret = asslib -> asset(api.m_url.fragment);
        
        if(!ret){
            assetWarning << "Unable to load (" << to_string(api.m_url) << "): no suitable libraries/loaders loaded it.";
            return {};
        }
        
        if(!ret->metaInfo().is_derived_or_this(am)){
            assetWarning << "Unable to load (" << to_string(api.m_url) << "): not a suitable asset type.";
            return {};
        }
        
        return ret;
    }
    
    std::error_code          Asset::_save(const Asset& asset, AssetSaveAPI&api)
    {
        if(!api.m_url.fragment.empty()){
            assetWarning << "Asset saving to '" << to_string(api.m_url) << "' does not support saving into libraries.";
            return errors::todo();
        }
        
        if(!is_similar(api.m_url.scheme, "file")){
            assetWarning << "Asset saving to '" << to_string(api.m_url) << "' does not support saving to non-files.";
            return errors::todo();
        }
        
        return _save_file(asset, api);
    }

    std::error_code          Asset::_save_file(const Asset& asset, AssetSaveAPI& api)
    {
        static Repo& _r     = repo();
        static Cache& _c    = cache();
        
        const AssetMeta&    am  = asset.metaInfo();

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
        for(auto& itr : as_iterable(_r.savers.equal_range(ext))){
            const Saver* sv = itr.second;
            if(!sv)
                continue;
            if(!sv->asset().is_base_or_this(am))
                continue;
                
            std::error_code ec;
            try {
                ec = sv -> save(asset, api.m_url, api);
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
                assetInfo << "Asset saved '" << to_string(api.m_url) << "'";
                saved = true;
                break;
            }

            assetWarning << "Asset unable to save to '" << to_string(api.m_url) << "': " << ec.message();
        }
        
        if(!saved)
            return errors::no_savers_applicable(); 
            
        
        if(existing){
            if(backup){
                file_backup(orig.path.c_str());
            }
            rename(api.m_url.path.c_str(), orig.path.c_str());
        }

        if(api.m_options.set_name && !asset.m_readonly && (asset.m_url != orig) && !_c.contains(asset.id())){
            const_cast<Asset&>(asset).m_url   = orig;
        }

        return {};
    }

    void Asset::add_infoer(Infoer*d) 
    {
        if(Meta::thread_safe_write()){
            repo().inject(d);
        } else if(d)
            delete d;
    }
    
    void Asset::add_loader(Loader*d)
    {
        if(Meta::thread_safe_write()){
            repo().inject(d);
        } else if(d)
            delete d;
    }

    void    Asset::add_library(const AssetLibraryCPtr& alp)
    {
        if(!alp)
            return;
        if(!Meta::thread_safe_write())
            return ;
        repo().search.push_back(alp);
    }
    
    void    Asset::add_path(const std::filesystem::path& fp)
    {
        if(!Meta::thread_safe_write())
            return ;
        repo().inject(fp);
    }
        
    void    Asset::add_paths(std::string_view dd)
    {
        if(!Meta::thread_safe_write())
            return ;

        Repo&    _r = repo();
        vsplit(dd, ';', [&](std::string_view x){
            _r.inject(std::filesystem::path(trimmed(x)));
        });
    }

    void    Asset::add_saver(Saver*d)
    {
        if(Meta::thread_safe_write()){
            repo().inject(d);
        } else if(d)
            delete d;
    }


    AssetInfoCPtr    Asset::info(std::string_view spec, const AssetInfoOptions& options)
    {
        return info(meta<Asset>(), spec, options);
    }
    
    AssetInfoCPtr    Asset::info(const AssetMeta&am, std::string_view spec, const AssetInfoOptions& options)
    {
        AssetInfoAPI    api(options);
        api.m_url       = resolve(spec);
        api.m_spec      = spec;
        return _info(am, api);
    }

    AssetInfoCPtr    Asset::info(const UrlView& url, const AssetInfoOptions& options)
    {
        return info(meta<Asset>(), url, options);
    }

    AssetInfoCPtr    Asset::info(const AssetMeta& am, const UrlView& url, const AssetInfoOptions& options)
    {
        AssetInfoAPI    api(options);
        api.m_url   = copy(url);
        api.m_spec  = to_string(url);
        return _info(am, api);
    }
    
    AssetInfoCPtr    Asset::info(const std::filesystem::path& fp, const AssetInfoOptions& options)
    {
        return info(meta<Asset>(), fp, options);
    }

    AssetInfoCPtr    Asset::info(const AssetMeta&am, const std::filesystem::path&fp, const AssetInfoOptions& options)
    {
        AssetInfoAPI    api(options);
        api.m_url.scheme    = "file";
        api.m_url.path      = fp.string();
        api.m_spec  = to_string(api.m_url);
        return _info(am, api);
    }

    AssetInfoCPtr    Asset::info(const std::filesystem::path&fp, std::string_view frag, const AssetInfoOptions& options)
    {
        return info(meta<Asset>(), fp, frag, options);
    }

    AssetInfoCPtr    Asset::info(const AssetMeta&am, const std::filesystem::path& fp, std::string_view frag, const AssetInfoOptions& options)
    {
        AssetInfoAPI    api(options);
        api.m_url.scheme    = "file";
        api.m_url.path      = fp.string();
        api.m_url.fragment  = std::string(frag);
        api.m_spec  = to_string(api.m_url);
        return _info(am, api);
    }

    AssetCPtr        Asset::load(std::string_view spec, const AssetLoadOptions& options)
    {
        return load(meta<Asset>(), spec, options);
    }

    AssetCPtr        Asset::load(const AssetMeta&am, std::string_view spec, const AssetLoadOptions& options)
    {
        AssetLoadAPI        api(options);
        api.m_url       = resolve(spec);
        api.m_spec      = spec;
        return _load(am, api);
    }

    AssetCPtr        Asset::load(const UrlView&url, const AssetLoadOptions& options)
    {
        return load(meta<Asset>(), url, options);
    }

    AssetCPtr        Asset::load(const AssetMeta&am, const UrlView&url, const AssetLoadOptions& options)
    {
        AssetLoadAPI    api(options);
        api.m_url   = copy(url);
        api.m_spec  = to_string(url);
        return _load(am, api);
    }
        
    AssetCPtr        Asset::load(const std::filesystem::path&fp, const AssetLoadOptions& options)
    {
        return load(meta<Asset>(), fp, options);
    }

    AssetCPtr        Asset::load(const AssetMeta&am, const std::filesystem::path& fp, const AssetLoadOptions& options)
    {
        AssetLoadAPI    api(options);
        api.m_url.scheme    = "file";
        api.m_url.path      = fp.string();
        api.m_spec  = to_string(api.m_url);
        return _load(am, api);
    }
    
    AssetCPtr        Asset::load(const std::filesystem::path& fp, std::string_view frag, const AssetLoadOptions& options)
    {
        return load(meta<Asset>(), fp, frag, options);
    }

    AssetCPtr        Asset::load(const AssetMeta&am, const std::filesystem::path&fp, std::string_view frag, const AssetLoadOptions& options)
    {
        AssetLoadAPI    api(options);
        api.m_url.scheme    = "file";
        api.m_url.path      = fp.string();
        api.m_url.fragment  = std::string(frag);
        api.m_spec  = to_string(api.m_url);
        return _load(am, api);
    }
        
    Url  Asset::resolve(std::string_view u)
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
                
                if(auto p = std::get_if<AssetLibraryCPtr>(&sp)){
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


/////////////////

    Asset::Asset()
    {
    }

    Asset::~Asset()
    {
    }

    std::string_view Asset::extension() const
    {
        if(!m_url.fragment.empty())
            return file_extension(m_url.fragment);
        if(!m_url.path.empty())
            return file_extension(m_url.path);
        return {};
    }

    void              Asset::inject()
    {
        m_readonly  = true;
        cache().inject(this);
    }

    std::error_code   Asset::save(const AssetSaveOptions& options) const
    {
        AssetSaveAPI    api(options);
        api.m_url      = m_url;
        return _save(*this, api);
    }

    std::error_code Asset::save_to(const std::filesystem::path&fp, const AssetSaveOptions& options) const
    {
        AssetSaveAPI    api(options);
        api.m_url.scheme    = "file";
        api.m_url.path      = fp.string();
        return _save(*this, api);
    }
    
    std::error_code Asset::save_to(const UrlView&url, const AssetSaveOptions& options) const
    {
        AssetSaveAPI    api(options);
        api.m_url      = copy(url);
        return _save(*this, api);
    }

    void Asset::set_url(const std::filesystem::path&fp) 
    {
        if(m_readonly)
            return;
        m_url.scheme    = "file";
        m_url.path = fp.string();
    }

    void Asset::set_url(const UrlView& url) 
    {
        if(m_readonly)
            return;
        m_url = copy(url);
    }

////////////////////////////////////////////////////////////////////////////////
}
