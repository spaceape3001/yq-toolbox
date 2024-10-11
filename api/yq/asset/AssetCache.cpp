////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "AssetCache.hpp"

#include <yq/core/Ref.hpp>
#include <yq/asset/Asset.hpp>

namespace yq {
    AssetCPtr AssetCache::_find(const std::filesystem::path&p) const
    {
        tbb::spin_rw_mutex::scoped_lock _lock(m_mutex, false);
        auto j = m_byPath.find(p);
        if(j == m_byPath.end())
            return {};
        auto k = m_byId.find(j->second);
        if(k == m_byId.end())
            return {};
        return k->second;
    }
    
    AssetCPtr    AssetCache::_find(uint64_t i) const
    {
        tbb::spin_rw_mutex::scoped_lock _lock(m_mutex, false);
        auto j = m_byId.find(i);
        if(j != m_byId.end())
            return j->second;
        return nullptr;
    }
    
    void    AssetCache::_insert(const Asset* a)
    {
        if(!a)
            return;
            
        tbb::spin_rw_mutex::scoped_lock _lock(m_mutex, true);
        auto [i,f]  = m_byId.try_emplace(a->id(),a);
        if(!f)
            return;

        if(!a->filepath().empty())
            m_byPath[a->filepath()] = a->id();    // clobber
    }

    bool        AssetCache::contains(const std::filesystem::path&pth) const
    {
        tbb::spin_rw_mutex::scoped_lock _lock(m_mutex, false);
        return m_byPath.contains(pth);
    }

    bool        AssetCache::contains(uint64_t i) const
    {
        tbb::spin_rw_mutex::scoped_lock _lock(m_mutex, false);
        return m_byId.contains(i);
    }

#if 0
    void        AssetCache::prune()
    {
        std::vector<AssetCPtr>  bye;
        
        //  TODO....
    }
#endif
    
    
    AssetCache::AssetCache()
    {
    }
    
    AssetCache::~AssetCache()
    {
    }
}
