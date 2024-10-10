////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#if !defined(YQUILL__API__CORE__TYPE__MAP__H__) || !defined(YQUILL__API__CORE__TYPE__VECTOR__H__)
    #error "Do NOT directly include this file!"
#endif

namespace yq {

    template <typename K, typename V, typename C>
    Vector<K>   Map<K,V,C>::keys() const
    {
        Vector<K> ret;
        ret.reserve(Map<K,V,C>::size());
        for(auto& itr : *this){
            ret << itr.first;
        }
        return ret;
    }

    template <typename K, typename V, typename C>
    Vector<V>   Map<K,V,C>::values() const
    {
        Vector<V> ret;
        ret.reserve(base_map::size());
        for(auto& itr : *this){
            ret << itr.second;
        }
        return ret;
    }

    template <typename K, typename V>
    Map<K,V>       makeMap(const Vector<std::pair<K,V>>&src)
    {
        return Map<K,V>(src.begin(), src.end());
    }

    template <typename K, typename V, typename C>
    Vector<std::pair<K,V>>  makeVector(const std::map<K,V,C>&src)
    {
        return Vector<std::pair<K,V>>(src.begin(), src.end());
    }

    template <typename K>
    struct MapReport {
        Vector<K>       added, changed, removed;
        
        bool    empty() const { return added.empty() && changed.empty() && removed.empty(); }
    };


    /*! \brief Describes the differences between two maps

        \param[in]  a       First Map
        \param[in]  b       Second Map
        \param[out] ret     Report of what's needed to go from first to second map
    */
    template <typename K, typename V, typename C>
    void    map_report(const std::map<K,V,C>&a, const std::map<K,V,C>&b, MapReport<K>& ret)
    {
        auto i = a.cbegin();
        auto j = b.cbegin();
        C       cmp;
        
        for(;;){
            if(i == a.end()){
                for(;j!=b.end();++j)
                    ret.added.push_back(j->first);
                break;
            } 
            
            if(j == b.end()){
                for(;i!=a.end();++i)
                    ret.removed.push_back(i->first);
                break;
            }

            for(;(i != a.end()) && cmp(i->first, j->first); ++i)      // i < j, so rmeoved
                ret.removed.push_back(i->first);
            if(i == a.end())
                continue;

            for(;(j != b.end()) && cmp(j->first, i->first); ++j)      // i > j, so added
                ret.added.push_back(j->first);
            if(j == b.end())
                continue;
            
            if(i->second != j->second)
                ret.changed.push_back(i->first);
            ++i, ++j;
        }
    }

}

