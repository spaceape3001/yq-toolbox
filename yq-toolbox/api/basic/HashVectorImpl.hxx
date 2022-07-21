////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#if !defined(YQUILL__API__CORE__TYPE__HASH__H__) || !defined(YQUILL__API__CORE__TYPE__VECTOR__H__)
    #error "Do NOT directly include this file!"
#endif

namespace yq {

    template <typename K, typename V>
    Vector<K>   Hash<K,V>::keys() const
    {
        Vector<K> ret;
        ret.reserve(Hash<K,V>::size());
        for(auto& itr : *this){
            ret << itr.first;
        }
        return ret;
    }

    template <typename K, typename V>
    Vector<V>   Hash<K,V>::values() const
    {
        Vector<V> ret;
        ret.reserve(Hash<K,V>::size());
        for(auto& itr : *this){
            ret << itr.second;
        }
        return ret;
    }


    template <typename K, typename V>
    Hash<K,V>       makeHash(const Vector<std::pair<K,V>>&src)
    {
        return Hash<K,V>(src.begin(), src.end());
    }


    template <typename K, typename V>
    Vector<std::pair<K,V>>  makeVector(const std::unordered_map<K,V>&src)
    {
        return Vector<std::pair<K,V>>(src.begin(), src.end());
    }

}
