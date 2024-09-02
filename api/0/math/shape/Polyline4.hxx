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

#include <0/math/shape/Polyline4.hpp>
#include <0/math/shape/PolylineData.hpp>
#include <0/math/utility.hpp>
#include <yq/container/vector_utils.hpp>

namespace yq {
    template <typename T> Polyline4<T>::Polyline4(const std::vector<Vector4<T>>&pts) : vertex(pts) {}
    template <typename T> Polyline4<T>::Polyline4(std::vector<Vector4<T>>&& pts) : vertex(std::move(pts)) {}
    template <typename T> Polyline4<T>::Polyline4(std::initializer_list<Vector4<T>> pts) : vertex(pts) {}
    
    #ifdef YQ_MATH_SEGMENT4_HPP
    template <typename T> Polyline4<T>::Polyline4(const Segment4<T>&s) : Polyline4({s.a, s.b}) {}
    #endif

    template <typename T>
    template <typename U>
    requires std::is_convertible_v<T,U>
    Polyline4<T>::operator Polyline4<U>() const
    {
        return Polyline4<U>(transform(vertex, [&](const Vector4<T>& v) -> Vector4<U> {
            return (Vector4<U>) v;
        }));
    }

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
    const Polyline4<T>&    Polyline4<T>::operator+() const
    {
        return *this;
    }
    
    template <typename T>
    Polyline4<T>           Polyline4<T>::operator-() const
    {
        return Polyline4(transform(vertex, [](const Vector4<T>& a) -> Vector4<T> {
            return -a;
        }));
    }
    
    template <typename T>
    Polyline4<T>   Polyline4<T>::operator+(const Vector4<T>&b) const
    {
        return Polyline4(span(vertex)+b);
    }
    
    template <typename T>
    Polyline4<T>&  Polyline4<T>::operator+=(const Vector4<T>& b)
    {
        for(Vector4<T>& v : vertex)
            v += b;
        return *this;
    }
    

    template <typename T>
    Polyline4<T>   Polyline4<T>::operator-(const Vector4<T>&b) const
    {
        return Polyline4(span(vertex)-b);
    }
    
    template <typename T>
    Polyline4<T>&  Polyline4<T>::operator-=(const Vector4<T>&b)
    {
        for(Vector4<T>& v : vertex)
            v -= b;
        return *this;
    }
    
    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    Polyline4<product_t<T,U>> Polyline4<T>::operator*(U b) const
    {
        return Polyline4<product_t<T,U>>(vertex*b);
    }
        
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
    Polyline4<T>& Polyline4<T>::operator*=(U b) 
    {
        for(Vector4<T>& v : vertex)
            v *= b;
        return *this;
    }

    #if defined(YQ_MATH_POLYLINE2_HPP) && defined(YQ_MATH_TENSOR_4_2_HPP)
    template <typename T>
        template <typename U>
    Polyline2<product_t<T,U>>   Polyline4<T>::operator*(const Tensor42<U>& b) const
    {
        return Polyline2<product_t<T,U>>(vertex * b);
    }
    #endif

    #if defined(YQ_MATH_POLYLINE3_HPP) && defined(YQ_MATH_TENSOR_4_3_HPP)
    template <typename T>
        template <typename U>
    Polyline3<product_t<T,U>>   Polyline4<T>::operator*(const Tensor43<U>&b) const
    {
        return Polyline3<product_t<T,U>>(vertex * b);
    }
    #endif

    #ifdef YQ_MATH_TENSOR_4_4_HPP
    template <typename T>
        template <typename U>
    Polyline4<product_t<T,U>>   Polyline4<T>::operator*(const Tensor44<U>&b) const
    {
        return Polyline4<product_t<T,U>>(vertex * b);
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_4_4_HPP
    template <typename T>
        template <typename U>
    requires self_multiply_v<T,U>
    Polyline4<T>&  Polyline4<T>::operator*=(const Tensor44<U>&b)
    {
        for(Vector4<T>& v : vertex)
            v *= b;
        return *this;
    }
    #endif

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    Polyline4<quotient_t<T,U>> Polyline4<T>::operator/(U b) const
    {
        return Polyline4<quotient_t<T,U>>(vertex / b);
    }
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_divide_v<T,U>)
    Polyline4<T>& Polyline4<T>::operator/=(U b)
    {
        for(Vector4<T>&v : vertex)
            v /= b;
        return *this;
    }

    #ifdef YQ_MATH_AXBOX4_HPP
    template <typename T>
    constexpr AxBox4<T>   Polyline4<T>::bounds() const noexcept
    {
        return AxBox4<T>(UNION, vertex);
    }
    #endif

    template <typename T>
    T       Polyline4<T>::length() const
    {
        T   ret = zero_v<T>;
        segments([&](const Vector4<T>& a, const Vector4<T>&b){
            ret += (a-b).length();
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
            #ifdef YQ_MATH_SEGMENT4_HPP
            if constexpr (std::is_invocable_v<Pred, Segment4<T>>){
                pred(Segment4<T>(vertex[i], vertex[i+1]));
            } else 
            #endif
            
            if constexpr (std::is_invocable_v<Pred, Vector4<T>, Vector4<T>>){
                pred(vertex[i], vertex[i+1]);
            }
        }
    }

    #ifdef YQ_MATH_SEGMENT4_HPP
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
    #endif

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    Polyline4<product_t<T,U>> operator*(T a, const Polyline4<U>&b)
    {   
        return Polyline4<product_t<T,U>>( a*b.vertex );
    }

    #ifdef YQ_MATH_AXBOX4_HPP
    template <typename T>
    AxBox4<T>   aabb(const Polyline4<T>&poly)
    {
        return poly.bounds();
    }
    #endif

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

    #ifdef YQ_MATH_SEGMENT4_HPP
    template <typename T>
    Polyline4<T> polyline(const Segment4<T>&seg)
    {
        return Polyline4<T>(seg);
    }
    #endif
}
