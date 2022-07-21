////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#if !defined(YQUILL__API__CORE__TYPE__SET__H__) || !defined(YQUILL__API__CORE__TYPE__VECTOR__H__)
    #error "Do NOT directly include this file!"
#endif

namespace yq {

    template <typename T>
    Set<T>          makeSet(const std::vector<T>&src)
    {
        return Set<T>(src.begin(), src.end());
    }

    template <typename T>
    Set<T>          makeSet(const Vector<T>&src)
    {
        return Set<T>(src.begin(), src.end());
    }


    template <typename T, typename C>
    Vector<T>       makeVector(const std::set<T,C>&src)
    {
        return Vector<T>(src.begin(), src.end());
    }
}
