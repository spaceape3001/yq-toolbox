////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#if !defined(YQUILL__API__CORE__TYPE__LIST__H__) || !defined(YQUILL__API__CORE__TYPE__SET__H__)
    #error "Do NOT directly include this file!"
#endif

namespace yq {
    template <typename T, typename C>
    List<T>         makeList(const std::set<T, C>&src)
    {
        return List<T>(src.begin(), src.end());
    }

    template <typename T>
    Set<T>          makeSet(const std::list<T>&src)
    {
        return Set<T>(src.begin(), src.end());
    }

}
