////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the polyline4 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <math/Polyline4.hpp>
#include <math/Segment4.hpp>

namespace yq {
    template <typename T> Polyline4<T>::Polyline4(const std::vector<Vector4<T>>&pts) : vertex(pts) {}
    template <typename T> Polyline4<T>::Polyline4(std::vector<Vector4<T>>&& pts) : vertex(std::move(pts)) {}
    template <typename T> Polyline4<T>::Polyline4(std::initializer_list<Vector4<T>> pts) : vertex(pts) {}
    template <typename T> Polyline4<T>::Polyline4(const Segment4<T>&s) : Polyline4({s.a, s.b}) {}

    template <typename T>
    Polyline4<T>::operator PolylineData<Vector4<T>>() const 
    {
        return { vertex };
    }

    template <typename T>
    Polyline4<T>&   Polyline4<T>::operator<<(const Vector4<T>& pt) 
    {
        vertex.push_back(pt);
        return *this;
    }

    template <typename T>
    constexpr AxBox4<T>   Polyline4<T>::bounds() const noexcept
    {
        if(vertex.empty())
            return nan_v<AxBox4<T>>;
        return AxBox4<T>(UNION, vertex);
    }

    template <typename T>
    T       Polyline4<T>::length() const
    {
        T   ret = zero_v<T>;
        segments([&](const Segment4<T>& seg){
            ret += seg.length();
        });
        return ret;
    }

    template <typename T>
        template <typename Pred>
    void    Polyline4<T>::segments(Pred pred) const
    {
        if(vertex.empty())
            return ;
        size_t n = vertex.size() - 1;
        for(size_t i=0;i<n;++i){
            if constexpr (std::is_invocable_v<Pred, Segment4<T>>){
                pred(Segment4<T>(vertex[i], vertex[i+1]));
            } else if constexpr (std::is_invocable_v<Pred, Vector4<T>, Vector4<T>>){
                pred(vertex[i], vertex[i+1]);
            }
        }
    }

    template <typename T>
    std::vector<Segment4<T>>    Polyline4<T>::segments() const
    {
        std::vector<Segment4<T>>    ret;
        ret.reserve(vertex.size());
        segments([&](const Segment4<T>& s){
            ret.push_back(s);
        });
        return ret;
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T>
    AxBox4<T>   aabb(const Polyline4<T>&poly)
    {
        return poly.bounds();
    }

    template <typename T>
    T       length(const Polyline4<T>& poly)
    {
        return poly.length();
    }

    template <typename T>
    Polyline4<T> polyline(std::span<const Vector4<T>> pts)
    {
        return Polyline4<T>(pts);
    }

    template <typename T>
    Polyline4<T> polyline(std::initializer_list<const Vector4<T>> pts)
    {
        return Polyline4<T>(pts);
    }

    template <typename T>
    Polyline4<T> polyline(std::vector<Vector4<T>>&& pts)
    {
        return Polyline4<T>(std::move(pts));
    }

    template <typename T>
    Polyline4<T> polyline(const Segment4<T>&seg)
    {
        return Polyline4<T>(seg);
    }
}
