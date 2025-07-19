////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/shape/Polymesh3.hpp>

namespace yq {
    template <typename T, typename I>
    const typename Polymesh3<T,I>::Face&  Polymesh3<T,I>::face(I i) const
    {
        static const Face kBadFace;
        if(i>=(I) faces.size())
            return kBadFace;
        return faces[i];
    }
    
    template <typename T, typename I>
    typename Polymesh3<T,I>::Face&  Polymesh3<T,I>::face(I i) 
    {
        static thread_local Face kBadFace;
        if(i>=(I) faces.size())
            return kBadFace;
        return faces[i];
    }
    
    template <typename T, typename I>
    const typename Polymesh3<T,I>::Line&  Polymesh3<T,I>::line(I i) const
    {
        static const Line kBadLine;
        if(i>=(I) lines.size())
            return kBadLine;
        return lines[i];
    }
    
    template <typename T, typename I>
    typename Polymesh3<T,I>::Line&  Polymesh3<T,I>::line(I i) 
    {
        static thread_local Line kBadLine;
        if(i>=(I) lines.size())
            return kBadLine;
        return lines[i];
    }
    
    template <typename T, typename I>
    const typename Polymesh3<T,I>::point_type&  Polymesh3<T,I>::vertex(I i) const
    {
        static const point_type kBadPoint;
        if(i >= (I) vertices.size())
            return kBadPoint;
        return vertices[i];
    }

    template <typename T, typename I>
    typename Polymesh3<T,I>::point_type&  Polymesh3<T,I>::vertex(I i) 
    {
        static thread_local point_type kBadPoint;
        if(i >= vertices.size())
            return kBadPoint;
        return vertices[i];
    }

    template <typename T, typename I>
    bool Polymesh3<T,I>::operator==(const Polymesh3&) const = default;

    ////////////////////////////////////////////////////////////////////////////

    template <typename T, typename I>
    bool Polymesh3<T,I>::Face::operator==(const Face&) const = default;

    ////////////////////////////////////////////////////////////////////////////

    template <typename T, typename I>
    bool Polymesh3<T,I>::Line::operator==(const Line&) const = default;

}
