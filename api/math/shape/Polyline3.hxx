////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the polyline3 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <math/shape/Polyline3.hpp>
#include <math/shape/PolylineData.hpp>
#include <math/utility.hpp>

namespace yq {
    template <typename T> Polyline3<T>::Polyline3(const std::vector<Vector3<T>>&pts) : vertex(pts) {}
    template <typename T> Polyline3<T>::Polyline3(std::vector<Vector3<T>>&& pts) : vertex(std::move(pts)) {}
    template <typename T> Polyline3<T>::Polyline3(std::initializer_list<Vector3<T>> pts) : vertex(pts) {}
    
    #ifdef YQ_MATH_SEGMENT3_HPP
    template <typename T> Polyline3<T>::Polyline3(const Segment3<T>&s) : Polyline3({s.a, s.b}) {}
    #endif

    template <typename T>
    template <typename U>
    requires std::is_convertible_v<T,U>
    Polyline3<T>::operator Polyline3<U>() const
    {
        return Polyline3<U>(transform(vertex, [&](const Vector3<T>& v) -> Vector3<U> {
            return (Vector3<U>) v;
        }));
    }

    template <typename T>
    Polyline3<T>::operator PolylineData<Vector3<T>>() const 
    {
        return { vertex };
    }

    template <typename T>
    Polyline3<T>&   Polyline3<T>::operator<<(const Vector3<T>& pt) 
    {
        vertex.push_back(pt);
        return *this;
    }

    template <typename T>
    const Polyline3<T>&    Polyline3<T>::operator+() const
    {
        return *this;
    }
    
    template <typename T>
    Polyline3<T>           Polyline3<T>::operator-() const
    {
        return Polyline3(transform(vertex, [](const Vector3<T>& a) -> Vector3<T> {
            return -a;
        }));
    }
    
    template <typename T>
    Polyline3<T>   Polyline3<T>::operator+(const Vector3<T>&b) const
    {
        return Polyline3(vertex+b);
    }
    
    template <typename T>
    Polyline3<T>&  Polyline3<T>::operator+=(const Vector3<T>& b)
    {
        for(Vector3<T>& v : vertex)
            v += b;
        return *this;
    }
    

    template <typename T>
    Polyline3<T>   Polyline3<T>::operator-(const Vector3<T>&b) const
    {
        return Polyline3(vertex-b);
    }
    
    template <typename T>
    Polyline3<T>&  Polyline3<T>::operator-=(const Vector3<T>&b)
    {
        for(Vector3<T>& v : vertex)
            v -= b;
        return *this;
    }
    
    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    Polyline3<product_t<T,U>> Polyline3<T>::operator*(U b) const
    {
        return Polyline3<product_t<T,U>>(vertex*b);
    }
        
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_mul_v<T,U>)
    Polyline3<T>& Polyline3<T>::operator*=(U b) 
    {
        for(Vector3<T>& v : vertex)
            v *= b;
        return *this;
    }

    #if defined(YQ_MATH_POLYLINE2_HPP) && defined(YQ_MATH_TENSOR_3_2_HPP)
    template <typename T>
        template <typename U>
    Polyline2<product_t<T,U>>   Polyline3<T>::operator*(const Tensor32<U>& b) const
    {
        return Polyline2<product_t<T,U>>(vertex * b);
    }
    #endif

    #ifdef YQ_MATH_TENSOR_3_3_HPP
    template <typename T>
        template <typename U>
    Polyline3<product_t<T,U>>   Polyline3<T>::operator*(const Tensor33<U>&b) const
    {
        return Polyline3<product_t<T,U>>(vertex * b);
    }
    #endif

    #if defined(YQ_MATH_POLYLINE4_HPP) && defined(YQ_MATH_TENSOR_3_4_HPP)
    template <typename T>
        template <typename U>
    Polyline4<product_t<T,U>>   Polyline3<T>::operator*(const Tensor34<U>&b) const
    {
        return Polyline4<product_t<T,U>>(vertex * b);
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_3_3_HPP
    template <typename T>
        template <typename U>
    requires self_mul_v<T,U>
    Polyline3<T>&  Polyline3<T>::operator*=(const Tensor33<U>&b)
    {
        for(Vector3<T>& v : vertex)
            v *= b;
        return *this;
    }
    #endif

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    Polyline3<quotient_t<T,U>> Polyline3<T>::operator/(U b) const
    {
        return Polyline3<quotient_t<T,U>>(vertex / b);
    }
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_div_v<T,U>)
    Polyline3<T>& Polyline3<T>::operator/=(U b)
    {
        for(Vector3<T>&v : vertex)
            v /= b;
        return *this;
    }
    
    #ifdef YQ_MATH_AXBOX3_HPP
    template <typename T>
    constexpr AxBox3<T>   Polyline3<T>::bounds() const noexcept
    {
        return AxBox3<T>(UNION, vertex);
    }
    #endif

    template <typename T>
    T       Polyline3<T>::length() const
    {
        T   ret = zero_v<T>;
        segments([&](const Vector3<T>& a, const Vector3<T>&b){
            ret += (a-b).length();
        });
        return ret;
    }

    template <typename T>
        template <typename Pred>
    void    Polyline3<T>::segments(Pred pred) const
    {
        if(vertex.empty())
            return ;
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
    std::vector<Segment3<T>>    Polyline3<T>::segments() const
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
    Polyline3<product_t<T,U>> operator*(T a, const Polyline3<U>&b)
    {   
        return Polyline3<product_t<T,U>>( a*b.vertex );
    }

    #ifdef YQ_MATH_AXBOX3_HPP
    template <typename T>
    AxBox3<T>   aabb(const Polyline3<T>&poly)
    {
        return poly.bounds();
    }
    #endif

    template <typename T>
    T       length(const Polyline3<T>& poly)
    {
        return poly.length();
    }

    template <typename T>
    Polyline3<T> polyline(std::span<const Vector3<T>> pts)
    {
        return Polyline3<T>(pts);
    }

    template <typename T>
    Polyline3<T> polyline(std::initializer_list<const Vector3<T>> pts)
    {
        return Polyline3<T>(pts);
    }

    template <typename T>
    Polyline3<T> polyline(std::vector<Vector3<T>>&& pts)
    {
        return Polyline3<T>(std::move(pts));
    }

    #ifdef YQ_MATH_SEGMENT3_HPP
    template <typename T>
    Polyline3<T> polyline(const Segment3<T>&seg)
    {
        return Polyline3<T>(seg);
    }
    #endif
}
