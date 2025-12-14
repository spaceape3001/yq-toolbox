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
    
        mutable tbb::spin_rw_mutex                         mutex;
        std::unordered_map<uint64_t, ResourceCPtr>         byId;       //!< Resource cache (by ID)
        std::multimap<UrlView, ResourceCPtr>               byUrl;      //!< Resource cache (by URL)
        std::map<UrlView, ResourceLibraryCPtr>             libraries;  //!< Currently loaded libraries
        std::unordered_map<uint64_t, ResourceInfoCPtr>     infoById;   //!< Resource Info cache (by ID)
        std::multimap<UrlView, ResourceInfoCPtr>           infoByUrl;  //!< Resource Info cache (by URL)
        
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
                bool swapped     = false;
                bool existing    = false;
                lock_t  _lock(mutex, true);
                byId[ap->id()]  = ap;
                auto r = byUrl.equal_range(ap->url());
                for(auto i =r.first; i != r.second; ++i){
                    if(i->second->id() == ap->id()){
                        existing    = true;
                        break;
                    }
                }
                if(!existing){
                    for(auto i =r.first; i != r.second; ++i){
                        if(i->second->metaInfo().id() == ap->metaInfo().id()){
                            std::swap(i->second, ap);
                            swapped =true;
                            break;
                        }
                    }
                    if(!swapped)
                        byUrl.insert({ap->url(), ap});
                }
                
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
                bool    swapped = false;
                lock_t  _lock(mutex, true);
                infoById[ap->id()]  = ap;
                auto r = infoByUrl.equal_range(ap->url());
                for(auto i = r.first; i!=r.second; ++i){
                    if(i->second->metaInfo().id() == ap->metaInfo().id()){
                        std::swap(i->second, ap);
                        swapped =true;
                        break;
                    }
                }
                if(!swapped)
                    infoByUrl.insert({ap->url(), ap});
                    
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

        ResourceCPtr   lookup(const UrlView& uv, const ResourceMeta& am) const
        {
            lock_t  _lock(mutex, false);
            auto r = byUrl.equal_range(uv);
            for(auto i = r.first; i!=r.second; ++i){
                if(i->second && i->second->metaInfo().is_base_or_this(am))
                    return i->second;
            }
            return {};
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

