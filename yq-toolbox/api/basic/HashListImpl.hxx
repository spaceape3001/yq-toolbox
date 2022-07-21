////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#if !defined(YQUILL__API__CORE__TYPE__LIST__H__) || !defined(YQUILL__API__CORE__TYPE__HASH__H__)
    #error "Do NOT directly include this file!"
#endif

namespace yq {
    template <typename K, typename V>
    Hash<K,V>       makeHash(const List<std::pair<K,V>>&src)
    {
        return Hash<K,V>(src.begin(), src.end());
    }

    template <typename K, typename V>
    List<std::pair<K,V>>    makeList(const std::unordered_map<K,V>&src)
    {
        return List<std::pair<K,V>>(src.begin(), src.end());
    }

}
