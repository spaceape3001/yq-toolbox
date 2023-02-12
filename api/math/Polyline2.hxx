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
#include <math/utility.hpp>

namespace yq {
    template <typename T> Polyline2<T>::Polyline2(const std::vector<Vector2<T>>&pts) : vertex(pts) {}
    template <typename T> Polyline2<T>::Polyline2(std::vector<Vector2<T>>&& pts) : vertex(std::move(pts)) {}
    template <typename T> Polyline2<T>::Polyline2(std::initializer_list<Vector2<T>> pts) : vertex(pts) {}
    template <typename T> Polyline2<T>::Polyline2(const Segment2<T>&s) : Polyline2({s.a, s.b}) {}

    template <typename T>
    template <typename U>
    requires std::is_convertible_v<T,U>
    Polyline2<T>::operator Polyline2<U>() const
    {
        return Polyline2<U>(transform(vertex, [&](const Vector2<T>& v) -> Vector2<U> {
            return (Vector2<U>) v;
        }));
    }

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
    const Polyline2<T>&    Polyline2<T>::operator+() const
    {
        return *this;
    }
    
    template <typename T>
    Polyline2<T>           Polyline2<T>::operator-() const
    {
        return Polyline2(transform(vertex, [](const Vector2<T>& a) -> Vector2<T> {
            return -a;
        }));
    }
    
    template <typename T>
    Polyline2<T>   Polyline2<T>::operator+(const Vector2<T>&b) const
    {
        return Polyline2(vertex+b);
    }
    
    template <typename T>
    Polyline2<T>&  Polyline2<T>::operator+=(const Vector2<T>& b)
    {
        for(Vector2<T>& v : vertex)
            v += b;
        return *this;
    }
    

    template <typename T>
    Polyline2<T>   Polyline2<T>::operator-(const Vector2<T>&b) const
    {
        return Polyline2(vertex-b);
    }
    
    template <typename T>
    Polyline2<T>&  Polyline2<T>::operator-=(const Vector2<T>&b)
    {
        for(Vector2<T>& v : vertex)
            v -= b;
        return *this;
    }

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    Polyline2<product_t<T,U>> Polyline2<T>::operator*(U b) const
    {
        return Polyline2<product_t<T,U>>(vertex*b);
    }
        
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_mul_v<T,U>)
    Polyline2<T>& Polyline2<T>::operator*=(U b) 
    {
        for(Vector2<T>& v : vertex)
            v *= b;
        return *this;
    }

    template <typename T>
        template <typename U>
    Polyline2<product_t<T,U>>   Polyline2<T>::operator*(const Tensor22<U>& b) const
    {
        return Polyline2<product_t<T,U>>(vertex * b);
    }

    template <typename T>
        template <typename U>
    Polyline3<product_t<T,U>>   Polyline2<T>::operator*(const Tensor23<U>&b) const
    {
        return Polyline3<product_t<T,U>>(vertex * b);
    }

    template <typename T>
        template <typename U>
    Polyline4<product_t<T,U>>   Polyline2<T>::operator*(const Tensor24<U>&b) const
    {
        return Polyline4<product_t<T,U>>(vertex * b);
    }
    
    template <typename T>
        template <typename U>
    requires self_mul_v<T,U>
    Polyline2<T>&  Polyline2<T>::operator*=(const Tensor22<U>&b)
    {
        for(Vector2<T>& v : vertex)
            v *= b;
        return *this;
    }

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    Polyline2<quotient_t<T,U>> Polyline2<T>::operator/(U b) const
    {
        return Polyline2<quotient_t<T,U>>(vertex / b);
    }
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_div_v<T,U>)
    Polyline2<T>& Polyline2<T>::operator/=(U b)
    {
        for(Vector2<T>&v : vertex)
            v /= b;
        return *this;
    }

    template <typename T>
    constexpr AxBox2<T>   Polyline2<T>::bounds() const noexcept
    {
        return AxBox2<T>(UNION, vertex);
    }

    template <typename T>
    T       Polyline2<T>::length() const
    {
        T   ret = zero_v<T>;
        segments([&](const Vector2<T>& a, const Vector2<T>&b){
            ret += (a-b).length();
        });
        return ret;
    }

    template <typename T>
        template <typename Pred>
    void    Polyline2<T>::segments(Pred pred) const
    {
        if(vertex.empty())
            return ;
        size_t n = vertex.size() - 1;
        for(size_t i=0;i<n;++i){
            if constexpr (std::is_invocable_v<Pred, Segment2<T>>){
                pred(Segment2<T>(vertex[i], vertex[i+1]));
            } else if constexpr (std::is_invocable_v<Pred, Vector2<T>, Vector2<T>>){
                pred(vertex[i], vertex[i+1]);
            }
        }
    }

    template <typename T>
    std::vector<Segment2<T>>    Polyline2<T>::segments() const
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

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    Polyline2<product_t<T,U>> operator*(T a, const Polyline2<U>&b)
    {   
        return Polyline2<product_t<T,U>>( a*b.vertex );
    }

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
