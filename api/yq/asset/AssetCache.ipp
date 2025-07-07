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


#if 0


#include <filesystem>
#include <map>
#include <unordered_map>

#include <yq/typedef/asset.hpp>
#include <yq/typedef/filesystem_path.hpp>
#include <yq/typedef/url.hpp>

namespace yq {
    
    /*! \brief An asset cache retains the data
    
        Most all engine components will query the cache for the data, if not present, loads it.  (Compiling first, if necessary)
    */
    class AssetCache {
    public:
    
            //  sweeps away old ones
        //void        prune();
        
        //bool        contains(const std::filesystem::path&) const;
        //! TRUE if we contain the specified url (exact & full)
        bool        contains(const Url&) const;
        bool        contains(uint64_t) const;
    
    protected:
        AssetCPtr   _find(const Url&) const;
        AssetCPtr   _find(uint64_t) const;
        
        //! Returns the other one if there's a collision on insert
        void        _insert(const Asset*);
        
        AssetCache();
        ~AssetCache();
        
    private:

        mutable tbb::spin_rw_mutex                  m_mutex;
        std::unordered_map<uint64_t, AssetCPtr>     m_byId;
        //std::map<std::filesystem::path, uint64_t>   m_byPath;
        std::map<Url, uint64_t>                     m_byUrl;
        
        AssetCache(const AssetCache&) = delete;
        AssetCache(AssetCache&&) = delete;
        AssetCache& operator=(const AssetCache&) = delete;
        AssetCache& operator=(AssetCache&&) = delete;
    };
}
#endif
