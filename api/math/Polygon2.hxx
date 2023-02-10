////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the polygon2 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <math/AxBox2.hpp>
#include <math/PolygonData.hpp>
#include <math/Polygon2.hpp>
#include <math/Triangle2.hpp>

namespace yq {
    template <typename T> Polygon2<T>::Polygon2(const std::vector<Vector2<T>>&pts) : vertex(pts) {}
    template <typename T> Polygon2<T>::Polygon2(std::vector<Vector2<T>>&& pts) : vertex(std::move(pts)) {}
    template <typename T> Polygon2<T>::Polygon2(std::initializer_list<Vector2<T>> pts) : vertex(pts) {}
    template <typename T> Polygon2<T>::Polygon2(std::span<const Vector2<T>> pts) : vertex(pts) {}

    template <typename T> Polygon2<T>::Polygon2(const AxBox2<T>&bx) : Polygon2({bx.ll(), bx.hl(), bx.hh(), bx.lh()}) {}
    template <typename T> Polygon2<T>::Polygon2(const Triangle2<T>& t) : Polygon2({t.a, t.b, t.c}) {}
    
    template <typename T>
    Polygon2<T>::operator PolygonData<Vector2<T>>() const 
    {
        return { vertex };
    }

    template <typename T>
    Polygon2<T>&   Polygon2<T>::operator<<(const Vector2<T>& pt) 
    {
        vertex.push_back(pt);
        return *this;
    }
    
    template <typename T>
        template <typename U>
    Polygon2<trait::product_t<T,U>>   Polygon2<T>::operator*(const Tensor22<U>& b) const
    {
        return Polygon2<trait::product_t<T,U>>(vertex * b);
    }

    template <typename T>
        template <typename U>
    Polygon3<trait::product_t<T,U>>   Polygon2<T>::operator*(const Tensor23<U>&b) const
    {
        return Polygon3<trait::product_t<T,U>>(vertex * b);
    }

    template <typename T>
        template <typename U>
    Polygon4<trait::product_t<T,U>>   Polygon2<T>::operator*(const Tensor24<U>&b) const
    {
        return Polygon4<trait::product_t<T,U>>(vertex * b);
    }
    
    template <typename T>
        template <typename U>
    requires trait::self_mul_v<T,U>
    Polygon2<T>&  Polygon2<T>::operator*=(const Tensor22<U>&b)
    {
        for(Vector2<T>& v : vertex)
            v *= b;
        return *this;
    }
    
    template <typename T>
    constexpr trait::square_t<T>    Polygon2<T>::area() const noexcept
    {
        return 0.5*abs(point_area());
    }

    template <typename T>
    constexpr AxBox2<T>   Polygon2<T>::bounds() const noexcept
    {
        return AxBox2<T>(UNION, vertex);
    }

    template <typename T>
    constexpr bool    Polygon2<T>::is_ccw() const noexcept
    {
        return point_area() < zero_v<T>;
    }


    template <typename T>
    constexpr bool    Polygon2<T>::is_clockwise() const noexcept
    {
        return point_area() > zero_v<T>;
    }
    
    template <typename T>
    T       Polygon2<T>::perimeter() const
    {
        T   ret = zero_v<T>;
        segments([&](const Segment2<T>& seg){
            ret += seg.length();
        });
        return ret;
    }

    template <typename T>
    constexpr trait::square_t<T>    Polygon2<T>::point_area() const noexcept
    {
        return delta_area(vertex);
    }

    template <typename T>
        template <typename Pred>
    void    Polygon2<T>::segments(Pred pred) const
    {
        if(vertex.empty())
            return ;
            
        if constexpr (std::is_invocable_v<Pred, Segment2<T>>){
            pred(Segment2<T>(vertex.back(), vertex.front));
        } else if constexpr (std::is_invocable_v<Pred, Vector2<T>, Vector2<T>>){
            pred(vertex.back(), vertex.front);
        }

        size_t n = vertex.size() - 1;
        for(size_t i=0;i<n;++i){
            if constexpr (std::is_invocable_v<Pred, Segment2<T>>){
                pred(Segment2<T>(vertex[i], vertex[i+1]));
            } else if constexpr (std::is_invocable_v<Pred, Vector2<T>, Vector2<T>>){
                pred(vertex[i], vertex[i+1]);
            }
        }
    }

    //! Converts the polygon to segments
    template <typename T>
    std::vector<Segment2<T>>    Polygon2<T>::segments() const
    {
        std::vector<Segment2<T>>    ret;
        ret.reserve(vertex.size());
        segments([&](const Segment2<T>& s){
            ret.push_back(s);
        });
        return ret;
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T>
    AxBox2<T>   aabb(const Polygon2<T>&poly)
    {
        return poly.bounds();
    }


    template <typename T>
    trait::square_t<T>    area(const Polygon2<T>& poly)
    {
        return poly.area();
    }

    template <typename T>
    bool    is_ccw(const Polygon2<T>& poly)
    {
        return poly.is_ccw();
    }

    template <typename T>
    bool    is_clockwise(const Polygon2<T>& poly)
    {
        return poly.is_clockwise();
    }
    
    template <typename T>
    T       perimeter(const Polygon2<T>& poly)
    {
        return poly.perimeter();
    }

    template <typename T>
    Polygon2<T> polygon(const AxBox2<T>& ax)
    {
        return Polygon2<T>(ax);
    }

    template <typename T>
    Polygon2<T> polygon(const Triangle2<T>& tri)
    {
        return Polygon2<T>(tri);
    }

    template <typename T>
    Polygon2<T> polygon(std::span<const Vector2<T>> pts)
    {
        return Polygon2<T>(pts);
    }

    template <typename T>
    Polygon2<T> polygon(std::initializer_list<const Vector2<T>> pts)
    {
        return Polygon2<T>(pts);
    }

    template <typename T>
    Polygon2<T> polygon(std::vector<Vector2<T>>&& pts)
    {
        return Polygon2<T>(std::move(pts));
    }

}
