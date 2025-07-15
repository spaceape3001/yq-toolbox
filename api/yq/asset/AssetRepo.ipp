////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Asset.hpp"
#include "AssetDriver.hpp"

#include <yq/file/FileUtils.hpp>
#include <yq/text/IgCase.hpp>

#include <map>
#include <filesystem>
#include <variant>

namespace yq {
    struct Asset::Repo {
    
        /*
            Use Cases to consider
            
            1) General filesystem asset
            2) There's a hash, hinting to a library
            3) URL
            
        */
    
        using search_t          = std::variant<std::monostate, std::filesystem::path, AssetLibraryCPtr>;
        using infoer_mmap_t     = std::multimap<std::string, const AssetInfoer*, IgCase>;
        using loader_mmap_t     = std::multimap<std::string, const AssetLoader*, IgCase>;
        using saver_mmap_t      = std::multimap<std::string, const AssetSaver*, IgCase>;
        // ditto once we have the idea of "skimming" or similar
        
        std::vector<search_t>                   search;         //!< Search
        std::vector<const AssetMeta*>           assets;         //!< All registered asset classes
        std::vector<const AssetLibraryMeta*>    libraries;      //!< All registered library classes
        
        std::vector<const AssetDriver*>         drivers;        //!< Drivers
        infoer_mmap_t                           infoers;        //!< Infoing drivers
        loader_mmap_t                           loaders;        //!< Loading drivers
        saver_mmap_t                            savers;         //!< Saving drivers
        
        // todo_t                               schemes;        // (Thinking Servers)

        Repo(){}

        void    inject(AssetInfoer* d)
        {
            if(!d)
                return;
            drivers.push_back(d);
            for(auto& ext : d->extensions())
                infoers.insert({ ext, d });
        }

        void    inject(AssetLoader* d)
        {
            if(!d)
                return;
            drivers.push_back(d);
            for(auto& ext : d->extensions())
                loaders.insert({ ext, d });
        }
        
        void    inject(AssetSaver*d)
        {
            if(!d)
                return;
            drivers.push_back(d);
            for(auto& ext : d->extensions())
                savers.insert({ext, d});
        }
        
        void    inject(const std::filesystem::path& fp)
        {
            if(!file_exists(fp))
                return;
            std::error_code ec;
            if(!std::filesystem::is_directory(fp, ec))
                return;
            search.push_back(fp);
        }
    };
    
    Asset::Repo& Asset::repo()
    {
        static Repo s_repo;
        return s_repo;
    }
}
