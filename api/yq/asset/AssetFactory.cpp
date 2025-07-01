////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "AssetFactory.hpp"

#include <yq/asset/Asset.hpp>
#include <yq/asset/AssetLogging.hpp>
#include <yq/file/FileResolver.hpp>
#include <yq/file/FileUtils.hpp>
#include <filesystem>

namespace yq {

    /*
        Assets (Version 2)
        
        Terminology
            Asset       Anything that can be loaded (aka Resource)
            Factory     Loading from file
            Info        Information (unfortunately, the term was taken first by Meta and we're not rewriting)
            Library     Collection of Assets
    
    */

#if 0
    struct AssetFactory::Per {
        std::vector<loader_t>   loaders;
        std::vector<saver_t>    savers;
    };

    struct AssetFactory::Common {
        std::map<std::string_view, Per>     byExts;
    };
    
    struct AssetFactory::Impl {
    };
#endif
    
    AssetFactory::AssetFactory(const AssetMeta&ai, const std::source_location& sl) : m_asset(&ai), m_source(sl) //, m(std::make_unique<Impl>())
    {
    }
    
    AssetFactory::~AssetFactory()
    {
    }

    AssetCPtr    AssetFactory::_load(const Url& url, const AssetLoadOptions& options)
    {
        AssetCPtr  ret = _find(url);
        if(ret)
            return ret;
            
        std::error_code ecx;
        if(!std::filesystem::exists(url.path, ecx)){
            assetInfo << "File does not exist (" << to_string(url) << ")";
            return nullptr;
        }

        std::string    x  = file_extension(url);
        if(x.empty())     // no extension... abort
            return nullptr;
        //x   = x.substr(1);
        
        AssetPtr  loaded  = nullptr;

        for(const Loader* l : m_loaders){
            if(!l->extensions.contains(x))
                continue;
            
            try {
                loaded     = l->load(url, options);
            } 
            catch(std::error_code ec) {
                assetWarning << "Unable to load (" << to_string(url) << "): " << ec.message();
            }
            
            if(loaded)
                break;
        }
        
        if(!loaded)
            return nullptr;
            
        loaded -> m_url   = url;
        _insert(loaded.ptr());
        return loaded;
    }
    
    AssetCPtr    AssetFactory::_pload(std::string_view pp, const AssetLoadOptions& options)
    {
        std::filesystem::path   fp   = Asset::resolver().resolve(pp);
        if(fp.empty()){
            assetWarning << "Unable to resolve to file: " << pp;
            return nullptr;
        }
        return _load(to_url(fp), options);
    }
    
    AssetCPtr    AssetFactory::_pfind(std::string_view pp) const
    {
        std::filesystem::path   fp   = Asset::resolver().resolve(pp);
        if(fp.empty())
            return nullptr;
        return _find(to_url(fp));
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    AssetFactory::Loader::Loader(std::initializer_list<std::string_view> exts, const std::source_location& sl)
    {
        for(auto x : exts)
            extensions << std::string(x);
        location    = sl;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    AssetFactory::Saver::Saver(std::initializer_list<std::string_view> exts, const std::source_location& sl)
    {
        for(auto x : exts)
            extensions << std::string(x);
        location    = sl;
    }
}
