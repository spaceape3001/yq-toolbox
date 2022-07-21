////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#if !defined(YQUILL__API__CORE__TYPE__LIST__H__) || !defined(YQUILL__API__CORE__TYPE__VECTOR__H__)
    #error "Do NOT directly include this file!"
#endif

namespace yq {
    template <typename T>
    Vector<const T*> makeConstVector(const List<T*>&src)
    {
        return Vector<const T*>(src.begin(), src.end());
    }


    template <typename T>
    List<T>         makeList(const std::vector<T>&src)
    {
        return List<T>(src.begin(), src.end());
    }

    template <typename T>
    Vector<T>&    Vector<T>::operator += (const List<T>&src)
    {
        Vector<T>::insert(Vector<T>::end(), src.begin(), src.end());
        return *this;
    }


    template <typename T>
    Vector<T>       makeVector(const List<T>&src)
    {
        return Vector<T>(src.begin(), src.end());
    }

}
