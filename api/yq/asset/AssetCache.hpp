////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <filesystem>
#include <map>
#include <unordered_map>
#include <tbb/spin_rw_mutex.h>

#include <yq/typedef/asset.hpp>
#include <yq/typedef/filesystem_path.hpp>

namespace yq {
    
    /*! \brief An asset cache retains the data
    
        Most all engine components will query the cache for the data, if not present, loads it.  (Compiling first, if necessary)
        
        WARNING... this thing will LEAK if things are reloaded as the asset won't delete
    */
    class AssetCache {
    public:
    
            //  sweeps away old ones
        //void        prune();
        
        //! TRUE if we contain the specified filepath (exact & full)
        bool        contains(const std::filesystem::path&) const;
        bool        contains(uint64_t) const;
    
    protected:
        AssetCPtr   _find(const std::filesystem::path&) const;
        AssetCPtr   _find(uint64_t) const;
        
        //! Returns the other one if there's a collision on insert
        void                _insert(const Asset*);
        
        AssetCache();
        ~AssetCache();
        
    private:

        mutable tbb::spin_rw_mutex                  m_mutex;
        std::unordered_map<uint64_t, AssetCPtr>     m_byId;
        std::map<std::filesystem::path, uint64_t>   m_byPath;
        
        AssetCache(const AssetCache&) = delete;
        AssetCache(AssetCache&&) = delete;
        AssetCache& operator=(const AssetCache&) = delete;
        AssetCache& operator=(AssetCache&&) = delete;
    };
}
