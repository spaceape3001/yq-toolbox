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

#include <yq/shape/PolygonData.hpp>
#include <yq/shape/Polygon2.hpp>
#include <yq/container/vector_utils.hpp>

namespace yq {
    template <typename T> Polygon2<T>::Polygon2(const std::vector<Vector2<T>>&pts) : vertex(pts) {}
    template <typename T> Polygon2<T>::Polygon2(std::vector<Vector2<T>>&& pts) : vertex(std::move(pts)) {}
    template <typename T> Polygon2<T>::Polygon2(std::initializer_list<Vector2<T>> pts) : vertex(pts) {}
    template <typename T> Polygon2<T>::Polygon2(std::span<const Vector2<T>> pts) : vertex(pts) {}

    #ifdef YQ_MATH_AXBOX2_HPP
    template <typename T> Polygon2<T>::Polygon2(const AxBox2<T>&bx) : Polygon2({bx.ll(), bx.hl(), bx.hh(), bx.lh()}) {}
    #endif
    
    #ifdef YQ_MATH_QUADRILATERAL2_HPP
    template <typename T> Polygon2<T>::Polygon2(const Quadrilateral2<T>&q) : Polygon2({q.a, q.b, q.c, q.d }) {}
    #endif
    
    #ifdef YQ_MATH_RECTANGLE2_HPP
    template <typename T> Polygon2<T>::Polygon2(const Rectangle2<T>&r) : 
        Polygon2({r.southwest(), r.southeast(), r.northeast(), r.northwest()}) {}
    #endif
    
    #ifdef YQ_MATH_TRIANGLE2_HPP
    template <typename T> Polygon2<T>::Polygon2(const Triangle2<T>& t) : Polygon2({t.a, t.b, t.c}) {}
    #endif
    
    template <typename T>
    template <typename U>
    requires std::is_convertible_v<T,U>
    Polygon2<T>::operator Polygon2<U>() const
    {
        return Polygon2<U>(transform(vertex, [&](const Vector2<T>& v) -> Vector2<U> {
            return (Vector2<U>) v;
        }));
    }

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
    const Polygon2<T>&    Polygon2<T>::operator+() const
    {
        return *this;
    }
    
    template <typename T>
    Polygon2<T>           Polygon2<T>::operator-() const
    {
        return Polygon2(transform(vertex, [](const Vector2<T>& a) -> Vector2<T> {
            return -a;
        }));
    }
    
    template <typename T>
    Polygon2<T>   Polygon2<T>::operator+(const Vector2<T>&b) const
    {
        return Polygon2(span(vertex)+b);
    }
    
    template <typename T>
    Polygon2<T>&  Polygon2<T>::operator+=(const Vector2<T>& b)
    {
        for(Vector2<T>& v : vertex)
            v += b;
        return *this;
    }
    

    template <typename T>
    Polygon2<T>   Polygon2<T>::operator-(const Vector2<T>&b) const
    {
        return Polygon2(span(vertex)-b);
    }
    
    template <typename T>
    Polygon2<T>&  Polygon2<T>::operator-=(const Vector2<T>&b)
    {
        for(Vector2<T>& v : vertex)
            v -= b;
        return *this;
    }

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    Polygon2<product_t<T,U>> Polygon2<T>::operator*(U b) const
    {
        return Polygon2<product_t<T,U>>(vertex*b);
    }
        
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
    Polygon2<T>& Polygon2<T>::operator*=(U b) 
    {
        for(Vector2<T>& v : vertex)
            v *= b;
        return *this;
    }

    #ifdef YQ_MATH_TENSOR_2_2_HPP
    template <typename T>
        template <typename U>
    Polygon2<product_t<T,U>>   Polygon2<T>::operator*(const Tensor22<U>& b) const
    {
        return Polygon2<product_t<T,U>>(span(vertex) * b);
    }
    #endif
    
    #if defined(YQ_MATH_POLYGON3_HPP) && defined(YQ_MATH_TENSOR_2_3_HPP)
    template <typename T>
        template <typename U>
    Polygon3<product_t<T,U>>   Polygon2<T>::operator*(const Tensor23<U>&b) const
    {
        return Polygon3<product_t<T,U>>(span(vertex) * b);
    }
    #endif

    #if defined(YQ_MATH_POLYGON4_HPP) && defined(YQ_MATH_TENSOR_2_4_HPP)
    template <typename T>
        template <typename U>
    Polygon4<product_t<T,U>>   Polygon2<T>::operator*(const Tensor24<U>&b) const
    {
        return Polygon4<product_t<T,U>>(span(vertex) * b);
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_2_2_HPP
    template <typename T>
        template <typename U>
    requires self_multiply_v<T,U>
    Polygon2<T>&  Polygon2<T>::operator*=(const Tensor22<U>&b)
    {
        for(Vector2<T>& v : vertex)
            v *= b;
        return *this;
    }
    #endif

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    Polygon2<quotient_t<T,U>> Polygon2<T>::operator/(U b) const
    {
        return Polygon2<quotient_t<T,U>>(span(vertex) / b);
    }
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_divide_v<T,U>)
    Polygon2<T>& Polygon2<T>::operator/=(U b)
    {
        for(Vector2<T>&v : vertex)
            v /= b;
        return *this;
    }


    template <typename T>
    constexpr square_t<T>    Polygon2<T>::area() const noexcept
    {
        return 0.5*abs(point_area());
    }

    #ifdef YQ_MATH_AXBOX2_HPP
    template <typename T>
    constexpr AxBox2<T>   Polygon2<T>::bounds() const noexcept
    {
        return AxBox2<T>(UNION, vertex);
    }
    #endif

    template <typename T>
    constexpr Vector2<T>    Polygon2<T>::centroid() const noexcept
    {
        if(vertex.empty())
            return Vector2<T>(ZERO);
        if constexpr (is_floating_point_v<T>)
            return sum(vertex) / ieee754_t<T>(vertex.size());
        if constexpr (is_integer_v<T>)
            return sum(vertex) / vertex.size();
        return Vector2<T>(ZERO);
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
        segments([&](const Vector2<T>& a, const Vector2<T>&b){
            ret += (a-b).length();
        });
        return ret;
    }

    template <typename T>
    constexpr square_t<T>    Polygon2<T>::point_area() const noexcept
    {
        return delta_area(vertex);
    }

    template <typename T>
        template <typename Pred>
    void    Polygon2<T>::segments(Pred pred) const
    {
        if(vertex.empty())
            return ;
            
        #ifdef YQ_MATH_SEGMENT2_HPP
        if constexpr (std::is_invocable_v<Pred, Segment2<T>>){
            pred(Segment2<T>(vertex.back(), vertex.front));
        } else 
        #endif
        
        if constexpr (std::is_invocable_v<Pred, Vector2<T>, Vector2<T>>){
            pred(vertex.back(), vertex.front);
        }

        size_t n = vertex.size() - 1;
        for(size_t i=0;i<n;++i){
        
            #ifdef YQ_MATH_SEGMENT2_HPP
            if constexpr (std::is_invocable_v<Pred, Segment2<T>>){
                pred(Segment2<T>(vertex[i], vertex[i+1]));
            } else 
            #endif
            
            if constexpr (std::is_invocable_v<Pred, Vector2<T>, Vector2<T>>){
                pred(vertex[i], vertex[i+1]);
            }
        }
    }

    #ifdef YQ_MATH_SEGMENT2_HPP
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
    #endif

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    Polygon2<product_t<T,U>> operator*(T a, const Polygon2<U>&b)
    {   
        return Polygon2<product_t<T,U>>( a*b.vertex );
    }

    #ifdef YQ_MATH_AXBOX2_HPP
    template <typename T>
    AxBox2<T>   aabb(const Polygon2<T>&poly)
    {
        return poly.bounds();
    }
    #endif

    template <typename T>
    square_t<T>    area(const Polygon2<T>& poly)
    {
        return poly.area();
    }

    template <typename T>
    Vector2<T>  centroid(const Polygon2<T>& poly)
    {
        return poly.centroid();
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

    #ifdef YQ_MATH_AXBOX2_HPP
    template <typename T>
    Polygon2<T> polygon(const AxBox2<T>& ax)
    {
        return Polygon2<T>(ax);
    }
    #endif

    #ifdef YQ_MATH_TRIANGLE2_HPP
    template <typename T>
    Polygon2<T> polygon(const Triangle2<T>& tri)
    {
        return Polygon2<T>(tri);
    }
    #endif
    
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
