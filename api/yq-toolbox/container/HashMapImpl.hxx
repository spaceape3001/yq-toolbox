////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#if !defined(YQUILL__API__CORE__TYPE__HASH__H__) || !defined(YQUILL__API__CORE__TYPE__MAP__H__)
    #error "Do NOT directly include this file!"
#endif

namespace yq {
    template <typename K, typename V, typename C>
    Hash<K,V>       makeHash(const std::map<K,V,C>&src)
    {
        return Hash<K,V>(src.begin(), src.end());
    }

    template <typename K, typename V>
    Map<K,V>       makeMap(const std::unordered_map<K,V>&src)
    {
        return Map<K,V>(src.begin(), src.end());
    }
}
