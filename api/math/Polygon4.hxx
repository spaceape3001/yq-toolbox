////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the polygon4 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <math/Polygon4.hpp>

namespace yq {
    template <typename T> Polygon4<T>::Polygon4(const std::vector<Vector4<T>>&pts) : vertex(pts) {}
    template <typename T> Polygon4<T>::Polygon4(std::vector<Vector4<T>>&& pts) : vertex(std::move(pts)) {}
    template <typename T> Polygon4<T>::Polygon4(std::initializer_list<Vector4<T>> pts) : vertex(pts) {}
    template <typename T> Polygon4<T>::Polygon4(std::span<const Vector4<T>> pts) : vertex(pts) {}

    template <typename T> Polygon4<T>::Polygon4(const Triangle4<T>& t) : Polygon4({t.a, t.b, t.c}) {}
    
    template <typename T>
    Polygon4<T>::operator PolygonData<Vector4<T>>() const 
    {
        return { vertex };
    }

    template <typename T>
    Polygon4<T>&   Polygon4<T>::operator<<(const Vector4<T>& pt) 
    {
        vertex.push_back(pt);
        return *this;
    }

    template <typename T>
    constexpr AxBox4<T>   Polygon4<T>::bounds() const noexcept
    {
        return AxBox4<T>(UNION, vertex);
    }

    template <typename T>
    T       Polygon4<T>::perimeter() const
    {
        T   ret = zero_v<T>;
        segments([&](const Segment4<T>& seg){
            ret += seg.length();
        });
        return ret;
    }

    template <typename T>
        template <typename Pred>
    void    Polygon4<T>::segments(Pred pred) const
    {
        if(vertex.empty())
            return ;
            
        if constexpr (std::is_invocable_v<Pred, Segment4<T>>){
            pred(Segment4<T>(vertex.back(), vertex.front));
        } else if constexpr (std::is_invocable_v<Pred, Vector4<T>, Vector4<T>>){
            pred(vertex.back(), vertex.front);
        }

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
    std::vector<Segment4<T>>    Polygon4<T>::segments() const
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
    AxBox4<T>   aabb(const Polygon4<T>&poly)
    {
        return poly.bounds();
    }

    template <typename T>
    T       perimeter(const Polygon4<T>& poly)
    {
        return poly.perimeter();
    }


    template <typename T>
    Polygon4<T> polygon(const Triangle4<T>& tri)
    {
        return Polygon4<T>(tri);
    }

    template <typename T>
    Polygon4<T> polygon(std::span<const Vector4<T>> pts)
    {
        return Polygon4<T>(pts);
    }

    template <typename T>
    Polygon4<T> polygon(std::initializer_list<const Vector4<T>> pts)
    {
        return Polygon4<T>(pts);
    }

    template <typename T>
    Polygon4<T> polygon(std::vector<Vector4<T>>&& pts)
    {
        return Polygon4<T>(std::move(pts));
    }
}
