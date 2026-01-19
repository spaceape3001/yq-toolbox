////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Resource.hpp"
#include "ResourceDriver.hpp"

#include <yq/file/FileUtils.hpp>
#include <yq/text/IgCase.hpp>

#include <map>
#include <filesystem>
#include <variant>

namespace yq {
    struct Resource::Repo {
    
        /*
            Use Cases to consider
            
            1) General filesystem resource
            2) There's a hash, hinting to a library
            3) URL
            
        */
    
        using search_t          = std::variant<std::monostate, std::filesystem::path, ResourceLibraryCPtr>;
        using infoer_mmap_t     = std::multimap<std::string, const ResourceInfoer*, IgCase>;
        using loader_mmap_t     = std::multimap<std::string, const ResourceLoader*, IgCase>;
        using saver_mmap_t      = std::multimap<std::string, const ResourceSaver*, IgCase>;
        // ditto once we have the idea of "skimming" or similar
        
        std::vector<search_t>                       search;         //!< Search
        std::vector<const ResourceMeta*>            resources;         //!< All registered resource classes
        std::vector<const ResourceLibraryMeta*>     libraries;      //!< All registered library classes
        
        std::vector<const ResourceDriver*>          drivers;        //!< Drivers
        infoer_mmap_t                               infoers;        //!< Infoing drivers
        loader_mmap_t                               loaders;        //!< Loading drivers
        saver_mmap_t                                savers;         //!< Saving drivers
        loader_mmap_t                               yqload;         //!< YQ loaders
        
        // todo_t                               schemes;        // (Thinking Servers)

        Repo(){}


        void    inject(ResourceInfoer* d)
        {
            if(!d)
                return;
            drivers.push_back(d);
            for(auto& ext : d->extensions())
                infoers.insert({ ext, d });
        }

        void    inject(ResourceLoader* d)
        {
            if(!d)
                return;
            drivers.push_back(d);
            for(auto& ext : d->extensions())
                loaders.insert({ ext, d });
        }
        
        void    inject(ResourceSaver*d)
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
    
    Resource::Repo& Resource::repo()
    {
        static Repo s_repo;
        return s_repo;
    }
}
