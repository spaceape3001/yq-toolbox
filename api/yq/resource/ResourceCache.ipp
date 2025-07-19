////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Resource.hpp"
#include "ResourceInfo.hpp"
#include "ResourceLibrary.hpp"

#include <tbb/spin_rw_mutex.h>

namespace yq {
    struct Resource::Cache {
        using mutex_t   = tbb::spin_rw_mutex;
        using lock_t    = tbb::spin_rw_mutex::scoped_lock;
    
        mutable tbb::spin_rw_mutex                      mutex;
        std::unordered_map<uint64_t, ResourceCPtr>         byId;       //!< Resource cache (by ID)
        std::map<UrlView, ResourceCPtr>                    byUrl;      //!< Resource cache (by URL)
        std::map<UrlView, ResourceLibraryCPtr>             libraries;  //!< Currently loaded libraries
        std::unordered_map<uint64_t, ResourceInfoCPtr>     infoById;   //!< Resource Info cache (by ID)
        std::map<UrlView, ResourceInfoCPtr>                infoByUrl;  //!< Resource Info cache (by URL)
        
        //void    inject(ResourceLibraryCPtr alp)
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
        
        void    inject(ResourceCPtr ap)
        {
            if(!ap)
                return;
            
            ResourceLibraryCPtr lib = dynamic_cast<const ResourceLibrary*>(ap.ptr());
            
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
        
        void    inject(ResourceInfoCPtr ap)
        {
            if(!ap)
                return;
            
            //ResourceLibraryCPtr lib = dynamic_cast<const ResourceLibrary*>(ap.ptr());
            
            {
                lock_t  _lock(mutex, true);
                infoById[ap->id()]  = ap;
                auto [i,f]  = infoByUrl.insert({ap->url(), ap});
                if(!f && (ap != i->second))
                    std::swap(i->second, ap);
                    
                #if 0
                    //  if we're libraries....
                if(lib){
                    auto [j, g] = libraries.insert({lib->url(), lib});
                    if(!g && (lib != j->second))
                        std::swap(j->second, lib);
                }
                #endif
            }
        }

        ResourceCPtr   lookup(const UrlView& uv) const
        {
            lock_t  _lock(mutex, false);
            auto i = byUrl.find(uv);
            if(i == byUrl.end())
                return {};
            return i->second;
        }

        ResourceInfoCPtr   lookup(info_k, const UrlView& uv) const
        {
            lock_t  _lock(mutex, false);
            auto i = infoByUrl.find(uv);
            if(i == infoByUrl.end())
                return {};
            return i->second;
        }

        
        ResourceCPtr   lookup(uint64_t id) const
        {
            lock_t  _lock(mutex, false);
            auto i = byId.find(id);
            if(i == byId.end())
                return {};
            return i->second;
        }
        
        ResourceInfoCPtr   lookup(info_k, uint64_t id) const
        {
            lock_t  _lock(mutex, false);
            auto i = infoById.find(id);
            if(i == infoById.end())
                return {};
            return i->second;
        }

        bool        contains(const UrlView& uv) const
        {
            lock_t  _lock(mutex, false);
            return byUrl.contains(uv);
        }
        
        bool        contains(info_k, const UrlView& uv) const
        {
            lock_t  _lock(mutex, false);
            return infoByUrl.contains(uv);
        }

        bool        contains(uint64_t id) const
        {
            lock_t  _lock(mutex, false);
            return byId.contains(id);
        }

        bool        contains(info_k, uint64_t id) const
        {
            lock_t  _lock(mutex, false);
            return infoById.contains(id);
        }
    };
    
    Resource::Cache&   Resource::cache()
    {
        static Cache s_cache;
        return s_cache;
    }
    
}

