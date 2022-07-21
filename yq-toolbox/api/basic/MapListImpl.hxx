////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#if !defined(YQUILL__API__CORE__TYPE__LIST__H__) || !defined(YQUILL__API__CORE__TYPE__MAP__H__)
    #error "Do NOT directly include this file!"
#endif

namespace yq {

    template <typename K, typename V, typename C>
    List<std::pair<K,V>>    makeList(const std::map<K,V,C>&src)
    {
        return List<std::pair<K,V>>(src.begin(), src.end());
    }


    template <typename K, typename V>
    Map<K,V>       makeMap(const List<std::pair<K,V>>&src)
    {
        return Map<K,V>(src.begin(), src.end());
    }
}
