////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the polyline2 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <math/Polyline2.hpp>
#include <math/Segment2.hpp>

namespace yq {
    template <typename T> Polyline2<T>::Polyline2(const std::vector<Vector2<T>>&pts) : vertex(pts) {}
    template <typename T> Polyline2<T>::Polyline2(std::vector<Vector2<T>>&& pts) : vertex(std::move(pts)) {}
    template <typename T> Polyline2<T>::Polyline2(std::initializer_list<Vector2<T>> pts) : vertex(pts) {}
    template <typename T> Polyline2<T>::Polyline2(const Segment2<T>&s) : Polyline2({s.a, s.b}) {}

    template <typename T>
    Polyline2<T>::operator PolylineData<Vector2<T>>() const 
    {
        return { vertex };
    }

    template <typename T>
    Polyline2<T>&   Polyline2<T>::operator<<(const Vector2<T>& pt) 
    {
        vertex.push_back(pt);
        return *this;
    }

    template <typename T>
    constexpr AxBox2<T>   Polyline2<T>::bounds() const noexcept
    {
        if(vertex.empty())
            return nan_v<AxBox2<T>>;
        return AxBox2<T>(UNION, vertex);
    }

    template <typename T>
    T       Polyline2<T>::length() const
    {
        if(vertex.empty())
            return zero_v<T>;
        T   ret = zero_v<T>;
        size_t n = vertex.size() - 1;
        for(size_t i=0;i<n;++i)
            ret += (vertex[i+1]-vertex[i]).length();
        return ret;
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T>
    AxBox2<T>   aabb(const Polyline2<T>&poly)
    {
        return poly.bounds();
    }

    template <typename T>
    T       length(const Polyline2<T>& poly)
    {
        return poly.length();
    }

    template <typename T>
    Polyline2<T> polyline(std::span<const Vector2<T>> pts)
    {
        return Polyline2<T>(pts);
    }

    template <typename T>
    Polyline2<T> polyline(std::initializer_list<const Vector2<T>> pts)
    {
        return Polyline2<T>(pts);
    }

    template <typename T>
    Polyline2<T> polyline(std::vector<Vector2<T>>&& pts)
    {
        return Polyline2<T>(std::move(pts));
    }

    template <typename T>
    Polyline2<T> polyline(const Segment2<T>&seg)
    {
        return Polyline2<T>(seg);
    }
}
