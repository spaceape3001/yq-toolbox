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
    
    AssetFactory::AssetFactory(const AssetInfo&ai, const std::source_location& sl) : m_asset(&ai), m_source(sl)
    {
    }
    
    AssetFactory::~AssetFactory()
    {
    }

    AssetCPtr    AssetFactory::_load(const std::filesystem::path& fp, const AssetLoadOptions& options)
    {
        AssetCPtr  ret = _find(fp);
        if(ret)
            return ret;
            
        if(!std::filesystem::exists(fp)){
            assetInfo << "File does not exist (" << fp << ")";
            return nullptr;
        }

        std::string    x  = fp.extension().string();
        if(x.empty())      // no extension... abort
            return nullptr;
        x   = x.substr(1);
        
        AssetPtr  loaded  = nullptr;

        for(const Loader* l : m_loaders){
            if(!l->extensions.contains(x))
                continue;
            
            try {
                loaded     = l->load(fp, options);
            } 
            catch(std::error_code ec) {
                assetWarning << "Unable to load (" << fp << "): " << ec.message();
            }
            
            if(loaded)
                break;
        }
        
        if(!loaded)
            return nullptr;
            
        loaded -> m_filepath   = fp;
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
        return _load(fp, options);
    }
    
    AssetCPtr    AssetFactory::_pfind(std::string_view pp) const
    {
        std::filesystem::path   fp   = Asset::resolver().resolve(pp);
        if(fp.empty())
            return nullptr;
        return _find(fp);
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
