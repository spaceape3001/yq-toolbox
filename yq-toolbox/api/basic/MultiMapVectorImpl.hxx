////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#if !defined(YQUILL__API__CORE__TYPE__MULTI_MAP__H__) || !defined(YQUILL__API__CORE__TYPE__VECTOR__H__)
    #error "Do NOT directly include this file!"
#endif

namespace yq {

    template <typename K, typename V, typename C>
    V           MultiMap<K,V,C>::first(const std::vector<K>&ks, const V&def) const
    {
        for(K k : ks){
            auto itr = base_map::find(k);
            if(itr != base_map::end())
                return itr->second;
        }
        return def;
    }

    template <typename K, typename V, typename C>
    Vector<V>   MultiMap<K,V,C>::get(const K&k) const
    {
        Vector<V> ret;
        auto range  = base_map::equal_range(k);
        for(auto itr = range.first; itr != range.second; ++itr)
            ret << itr->second;
        return ret;
    }

    template <typename K, typename V, typename C>
    Vector<V>   MultiMap<K,V,C>::get(std::initializer_list<K> Ks) const
    {
        Vector<V> ret;
        for(const K k : Ks){
            auto range  = base_map::equal_range(k);
            for(auto itr = range.first; itr != range.second; ++itr)
                ret << itr->second;
        }
        return ret;
    }

    template <typename K, typename V, typename C>
    Vector<V>   MultiMap<K,V,C>::get(const Vector<K>&Ks) const
    {
        Vector<V> ret;
        for(const K k : Ks){
            auto range  = base_map::equal_range(k);
            for(auto itr = range.first; itr != range.second; ++itr)
                ret << itr->second;
        }
        return ret;
    }

    template <typename K, typename V, typename C>
    Vector<K>   MultiMap<K,V,C>::keys() const
    {
        Vector<K>   ret;
        ret.reserve(base_map::size());
        for(auto itr : *this)
            ret.push_back(itr.first);
        return ret;
    }

    template <typename K, typename V, typename C>
    Vector<V>   MultiMap<K,V,C>::values() const
    {
        Vector<V>   ret;
        ret.reserve(base_map::size());
        for(auto itr : *this)
            ret.push_back(itr.second);
        return ret;
    }

    template <typename K, typename V, typename C>
    void        MultiMap<K,V,C>::rekey(const K&from, const K&to)
    {
        //  eventually, something smarter will replace this....
        for(V& v : get(from))
            insert(to, v);
        base_map::erase(from);
    }



    template <typename K, typename V, typename C>
    Vector<K>   MultiMap<K,V,C>::unique_keys() const
    {
        Vector<K>   ret;
        ret.reserve(base_map::size());
        for(auto itr : *this){
            if(ret.empty())
                ret << itr.first;
            else if(ret.back() != itr.first)
                ret << itr.first;
        }
        return ret;
    }


}
