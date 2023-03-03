////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the polygon3 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <math/PolygonData.hpp>
#include <math/Polygon3.hpp>

namespace yq {
    template <typename T> Polygon3<T>::Polygon3(const std::vector<Vector3<T>>&pts) : vertex(pts) {}
    template <typename T> Polygon3<T>::Polygon3(std::vector<Vector3<T>>&& pts) : vertex(std::move(pts)) {}
    template <typename T> Polygon3<T>::Polygon3(std::initializer_list<Vector3<T>> pts) : vertex(pts) {}
    template <typename T> Polygon3<T>::Polygon3(std::span<const Vector3<T>> pts) : vertex(pts) {}

    #ifdef YQ_MATH_TRIANGLE3_HPP
    template <typename T> Polygon3<T>::Polygon3(const Triangle3<T>& t) : Polygon3({t.a, t.b, t.c}) {}
    #endif
    
    template <typename T>
    template <typename U>
    requires std::is_convertible_v<T,U>
    Polygon3<T>::operator Polygon3<U>() const
    {
        return Polygon3<U>(transform(vertex, [&](const Vector3<T>& v) -> Vector3<U> {
            return (Vector3<U>) v;
        }));
    }

    template <typename T>
    Polygon3<T>::operator PolygonData<Vector3<T>>() const 
    {
        return { vertex };
    }

    template <typename T>
    Polygon3<T>&   Polygon3<T>::operator<<(const Vector3<T>& pt) 
    {
        vertex.push_back(pt);
        return *this;
    }
    
    template <typename T>
    const Polygon3<T>&    Polygon3<T>::operator+() const
    {
        return *this;
    }
    
    template <typename T>
    Polygon3<T>           Polygon3<T>::operator-() const
    {
        return Polygon3(transform(vertex, [](const Vector3<T>& a) -> Vector3<T> {
            return -a;
        }));
    }
    
    template <typename T>
    Polygon3<T>   Polygon3<T>::operator+(const Vector3<T>&b) const
    {
        return Polygon3(vertex+b);
    }
    
    template <typename T>
    Polygon3<T>&  Polygon3<T>::operator+=(const Vector3<T>& b)
    {
        for(Vector3<T>& v : vertex)
            v += b;
        return *this;
    }
    

    template <typename T>
    Polygon3<T>   Polygon3<T>::operator-(const Vector3<T>&b) const
    {
        return Polygon3(vertex-b);
    }
    
    template <typename T>
    Polygon3<T>&  Polygon3<T>::operator-=(const Vector3<T>&b)
    {
        for(Vector3<T>& v : vertex)
            v -= b;
        return *this;
    }

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    Polygon3<product_t<T,U>> Polygon3<T>::operator*(U b) const
    {
        return Polygon3<product_t<T,U>>(vertex*b);
    }
        
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_mul_v<T,U>)
    Polygon3<T>& Polygon3<T>::operator*=(U b) 
    {
        for(Vector3<T>& v : vertex)
            v *= b;
        return *this;
    }

    #if defined(YQ_MATH_POLYGON2_HPP) && defined(YQ_MATH_TENSOR_3_2_HPP)
    template <typename T>
        template <typename U>
    Polygon2<product_t<T,U>>   Polygon3<T>::operator*(const Tensor32<U>& b) const
    {
        return Polygon2<product_t<T,U>>(vertex * b);
    }
    #endif

    #ifdef YQ_MATH_TENSOR_3_3_HPP
    template <typename T>
        template <typename U>
    Polygon3<product_t<T,U>>   Polygon3<T>::operator*(const Tensor33<U>&b) const
    {
        return Polygon3<product_t<T,U>>(vertex * b);
    }
    #endif

    #if defined(YQ_MATH_POLYGON4_HPP) && defined(YQ_MATH_TENSOR_3_4_HPP)
    template <typename T>
        template <typename U>
    Polygon4<product_t<T,U>>   Polygon3<T>::operator*(const Tensor34<U>&b) const
    {
        return Polygon4<product_t<T,U>>(vertex * b);
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_3_3_HPP
    template <typename T>
        template <typename U>
    requires self_mul_v<T,U>
    Polygon3<T>&  Polygon3<T>::operator*=(const Tensor33<U>&b)
    {
        for(Vector3<T>& v : vertex)
            v *= b;
        return *this;
    }
    #endif

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    Polygon3<quotient_t<T,U>> Polygon3<T>::operator/(U b) const
    {
        return Polygon3<quotient_t<T,U>>(vertex / b);
    }
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_div_v<T,U>)
    Polygon3<T>& Polygon3<T>::operator/=(U b)
    {
        for(Vector3<T>&v : vertex)
            v /= b;
        return *this;
    }

    #ifdef YQ_MATH_AXBOX3_HPP
    template <typename T>
    constexpr AxBox3<T>   Polygon3<T>::bounds() const noexcept
    {
        return AxBox3<T>(UNION, vertex);
    }
    #endif

    template <typename T>
    constexpr Vector3<T>    Polygon3<T>::centroid() const noexcept
    {
        if(vertex.empty())
            return Vector3<T>(ZERO);
        if constexpr (is_floating_point_v<T>)
            return sum(vertex) / ieee754_t<T>(vertex.size());
        if constexpr (is_integer_v<T>)
            return sum(vertex) / vertex.size();
        return Vector3<T>(ZERO);
    }

    template <typename T>
    T       Polygon3<T>::perimeter() const
    {
        T   ret = zero_v<T>;
        segments([&](const Vector3<T>& a, const Vector3<T>&b){
            ret += (a-b).length();
        });
        return ret;
    }
    
    template <typename T>
        template <typename Pred>
    void    Polygon3<T>::segments(Pred pred) const
    {
        if(vertex.empty())
            return ;
            
        #ifdef YQ_MATH_SEGMENT3_HPP
        if constexpr (std::is_invocable_v<Pred, Segment3<T>>){
            pred(Segment3<T>(vertex.back(), vertex.front));
        } else 
        #endif
        
        if constexpr (std::is_invocable_v<Pred, Vector3<T>, Vector3<T>>){
            pred(vertex.back(), vertex.front);
        }

        size_t n = vertex.size() - 1;
        for(size_t i=0;i<n;++i){
        
            #ifdef YQ_MATH_SEGMENT3_HPP
            if constexpr (std::is_invocable_v<Pred, Segment3<T>>){
                pred(Segment3<T>(vertex[i], vertex[i+1]));
            } else 
            #endif
            
            if constexpr (std::is_invocable_v<Pred, Vector3<T>, Vector3<T>>){
                pred(vertex[i], vertex[i+1]);
            }
        }
    }
    
    #ifdef YQ_MATH_SEGMENT3_HPP
    template <typename T>
    std::vector<Segment3<T>>    Polygon3<T>::segments() const
    {
        std::vector<Segment3<T>>    ret;
        ret.reserve(vertex.size());
        segments([&](const Segment3<T>& s){
            ret.push_back(s);
        });
        return ret;
    }
    #endif

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    Polygon3<product_t<T,U>> operator*(T a, const Polygon3<U>&b)
    {   
        return Polygon3<product_t<T,U>>( a*b.vertex );
    }

    template <typename T>
    AxBox3<T>   aabb(const Polygon3<T>&poly)
    {
        return poly.bounds();
    }

    template <typename T>
    Vector3<T>  centroid(const Polygon3<T>& poly)
    {
        return poly.centroid();
    }

    template <typename T>
    T       perimeter(const Polygon3<T>& poly)
    {
        return poly.perimeter();
    }

    #ifdef YQ_MATH_TRIANGLE3_HPP
    template <typename T>
    Polygon3<T> polygon(const Triangle3<T>& tri)
    {
        return Polygon3<T>(tri);
    }
    #endif

    template <typename T>
    Polygon3<T> polygon(std::span<const Vector3<T>> pts)
    {
        return Polygon3<T>(pts);
    }

    template <typename T>
    Polygon3<T> polygon(std::initializer_list<const Vector3<T>> pts)
    {
        return Polygon3<T>(pts);
    }

    template <typename T>
    Polygon3<T> polygon(std::vector<Vector3<T>>&& pts)
    {
        return Polygon3<T>(std::move(pts));
    }
}
