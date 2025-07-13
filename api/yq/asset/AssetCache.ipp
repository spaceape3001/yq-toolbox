////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Asset.hpp"
#include "AssetLibrary.hpp"

#include <tbb/spin_rw_mutex.h>

namespace yq {
    struct Asset::Cache {
        using mutex_t   = tbb::spin_rw_mutex;
        using lock_t    = tbb::spin_rw_mutex::scoped_lock;
    
        mutable tbb::spin_rw_mutex                      mutex;
        std::unordered_map<uint64_t, AssetCPtr>         byId;       //!< Asset cache (by ID)
        std::map<UrlView, AssetCPtr>                    byUrl;      //!< Asset cache (by URL)
        std::map<UrlView, AssetLibraryCPtr>             libraries;  //!< Currently loaded libraries
        
        //void    inject(AssetLibraryCPtr alp)
        //{
            //if(!alp)
                //return;
        
            //{
                //lock_t  _lock(mutex, true);
                //auto [i,f]  = libraries.insert({alp->url(), alp});
                //if(!f)
                    //std::swap(i->second, alp);
            //}
        //}
        
        void    inject(AssetCPtr ap)
        {
            if(!ap)
                return;
            
            AssetLibraryCPtr lib = dynamic_cast<const AssetLibrary*>(ap.ptr());
            
            {
                lock_t  _lock(mutex, true);
                byId[ap->id()]  = ap;
                auto [i,f]  = byUrl.insert({ap->url(), ap});
                if(!f && (ap != i->second))
                    std::swap(i->second, ap);
                    
                if(lib){
                    auto [j, g] = libraries.insert({lib->url(), lib});
                    if(!g && (lib != j->second))
                        std::swap(j->second, lib);
                }
            }
        }
        
        AssetCPtr   lookup(const UrlView& uv) const
        {
            lock_t  _lock(mutex, false);
            auto i = byUrl.find(uv);
            if(i == byUrl.end())
                return {};
            return i->second;
        }

        
        AssetCPtr   lookup(uint64_t id) const
        {
            lock_t  _lock(mutex, false);
            auto i = byId.find(id);
            if(i == byId.end())
                return {};
            return i->second;
        }
        
        bool        contains(const UrlView& uv) const
        {
            lock_t  _lock(mutex, false);
            return byUrl.contains(uv);
        }
        
        bool        contains(uint64_t id) const
        {
            lock_t  _lock(mutex, false);
            return byId.contains(id);
        }
    };
    
    Asset::Cache&   Asset::cache()
    {
        static Cache s_cache;
        return s_cache;
    }
    
}

