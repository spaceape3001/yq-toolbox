////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Asset.hpp"
#include "AssetMetaWriter.hpp"

#include <yq/tags.hpp>
#include <yq/text/match.hpp>
#include <yq/text/transform.hpp>
#include <yq/text/vsplit.hpp>

YQ_OBJECT_IMPLEMENT(yq::Asset)

namespace yq {

////////////////////////////////////////////////////////////////////////////////


    AssetMeta::AssetMeta(std::string_view zName, ObjectMeta& base, const std::source_location& sl) :
        ObjectMeta(zName, base, sl)
    {
        set(Flag::ASSET);
        Asset::repo().assets.push_back(this);
    }

////////////////////////////////////////////////////////////////////////////////


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

    void Asset::init_meta()
    {
        auto w = writer<Asset>();
        w.description("Asset (ie texture, mesh, shader, etc)");
        w.property("url", &Asset::m_url).tag({kTag_Save});
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


    Asset::Asset()
    {
    }

    Asset::~Asset()
    {
    }

////////////////////////////////////////////////////////////////////////////////

}



#if 0

#include "Asset.hpp"
#include <yq/keywords.hpp>
#include <variant>
#include <tbb/spin_rw_mutex.hpp>
#include <map>
#include <unordered_map>
#include <yq/container/set_utils.hpp>
#include <yq/errors.hpp>


namespace yq {

    namespace errors {
    }


    
////////////////////////////////////////////////////////////////////////////////

    
    
    AssetCPtr       Asset::_load(const AssetMeta& am, const Url& url, bool autoCache)
    {
        static Repo& _r = repo();
        bool isLibType  = am.is_derived_or_this(meta<AssetLibrary>());
        
        
        return {};  // TODO
    }
    
    
    struct SimpleURL {
        std::string_view    filepath;
        std::string_view    fragment;
    };
    
    std::variant<url_k, std::string_view, SimpleURL> simplex(std::string_view u)
    {
        auto hash   = u.find_first_of('#');
        auto colon  = u.find_first_of(':');
        
        if((colon != std::string_view::npos) && ((hash == std::string_view::npos) || (hash > colon))
            return URL;
        if(hash != std::string_view::npos){
            return SimpleURL{ u.substr(0, hash), u.substr(hash+1) };
        } else
            return u;
    }
    

    Url             Asset::_resolve(std::string_view partial)
    {
        if(partial.empty())
            return {};
    
        // alright... this needs to do it by parts...
        UrlView     u = urlview(partial);

        static Repo& _r = repo();
        return {}; // TODO
    }

    Asset::Repo& Asset::repo()
    {
        static Repo s_repo;
        return s_repo;
    }

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////




}




#include <yq/errors.hpp>
#include <yq/asset/Asset.hpp>
#include <yq/asset/AssetIO.hpp>
#include <yq/asset/AssetFactory.hpp>
#include <yq/asset/AssetMetaWriter.hpp>
#include <yq/asset/AssetLogging.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Meta.hpp>
#include <yq/file/FileUtils.hpp>
#include <yq/file/FileResolver.hpp>
#include <yq/text/transform.hpp>
#include <yq/text/vsplit.hpp>

#include <unistd.h>


namespace yq {

    //  If done, binary Cache will be SQLite based....

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    FileResolver&            Asset::_resolver()
    {
        static FileResolver s_ret;
        return s_ret;
    }

    const FileResolver&      Asset::resolver()
    {
        return _resolver();
    }

    void  Asset::resolver_add_path(const std::filesystem::path&fp)
    {
        if(Meta::thread_safe_write()){
            _resolver().add_path(fp);
        }
    }
    
    void  Asset::resolver_add_paths(std::string_view dd)
    {
        if(Meta::thread_safe_write()){
            auto& _r = _resolver();
            vsplit(dd, ';', [&](std::string_view x){
                _r.add_path(trimmed(dd));
            });
        }
    }
    
    std::filesystem::path    Asset::resolve(std::string_view x)
    {
        return resolver().resolve(x);
    }
    
    std::filesystem::path    Asset::resolve(full_k, std::string_view x)
    {
        return resolver().resolve(x);
    }
    
    std::filesystem::path    Asset::resolve(partial_k, std::string_view x)
    {
        return resolver().partial(x);
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Asset::Asset(const std::filesystem::path&fp)
    {
        set_url(fp);
    }
    
    std::filesystem::path           Asset::filepath() const
    {
        return m_url.path;
    }
    
    namespace errors {
        using filepath_existing             = error_db::entry<"Filepath already exists">;
        using no_file_extension             = error_db::entry<"No file extension provided to file">;
        using invalid_collision_strategy    = error_db::entry<"File collision strategy is invalid">;
        using no_savers_defined             = error_db::entry<"Asset class has NO saving functions defined">;
        using no_savers_applicable          = error_db::entry<"No file savers defined for given output">;
        using saving_exception              = error_db::entry<"Exception thrown during saving">;
    }

    std::error_code Asset::save_to(const std::filesystem::path& fp) const
    {
        return save_to(fp, AssetSaveOptions());
    }

    std::error_code Asset::save_to(const std::filesystem::path& fp, const AssetSaveOptions& options) const
    {
        if(fp.empty())
            return errors::filepath_empty();
            
        AssetFactory&   af = factory();
        if(af.m_savers.empty()){
            return errors::no_savers_defined();
        }
        
        std::string    x  = fp.extension().string();
        if(x.empty())      // no extension... abort
            return errors::no_file_extension();
        x   = x.substr(1);
        if(x.empty())      // no extension... abort
            return errors::no_file_extension();
        
        std::filesystem::path   save_file;
        bool    existing    = std::filesystem::exists(fp);
        if(existing){
            switch(options.collision){
            case FileCollisionStrategy::Abort:
                return errors::filepath_existing();
            case FileCollisionStrategy::Overwrite:
            case FileCollisionStrategy::Backup:
                save_file   = fp.string() + "~tmp";
                break;
            default:
                return errors::invalid_collision_strategy();
            }
        } else {
            save_file   = fp;
        }
        
        std::error_code     ec = errors::no_savers_applicable();
        Url     saveUrl  = to_url(save_file);
        
        for(const AssetFactory::Saver* s : af.m_savers){
            if(!s->extensions.contains(x))
                continue;
            try {
                ec  = s -> save(*this, saveUrl, options);
                if(ec != std::error_code())
                    continue;
                break;
            }
            catch(std::error_code ec2)
            {
                ec2 = ec;
            }
            #ifndef NDEBUG
            catch(...)
            {
                ec  = errors::saving_exception();
            }
            #endif
        }
        
        if(ec != std::error_code()){
            assetWarning << "Unable to save to file " << save_file << " (" << ec.message() << ")";
            return ec;
        }
        
        if(existing){
            if(options.collision == FileCollisionStrategy::Backup){
                file_backup(fp.c_str());
            }
            rename(save_file.c_str(), fp.c_str());
        }
        
        if(options.set_name && (fp.string() != m_url.path) && !af.contains(id())){
            const_cast<Asset*>(this) -> m_url  = to_url(fp);
        }

        return {};
    }

    void Asset::set_url(const std::filesystem::path&fp) 
    {
        m_url = to_url(fp);
    }

    void Asset::set_url(const Url& url) 
    {
        m_url = url;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
#endif
