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
    template <typename U>
    requires std::is_convertible_v<T,U>
    Polygon4<T>::operator Polygon4<U>() const
    {
        return Polygon4<U>(transform(vertex, [&](const Vector4<T>& v) -> Vector4<U> {
            return (Vector4<U>) v;
        }));
    }

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
    const Polygon4<T>&    Polygon4<T>::operator+() const
    {
        return *this;
    }
    
    template <typename T>
    Polygon4<T>           Polygon4<T>::operator-() const
    {
        return Polygon4(transform(vertex, [](const Vector4<T>& a) -> Vector4<T> {
            return -a;
        }));
    }
    
    template <typename T>
    Polygon4<T>   Polygon4<T>::operator+(const Vector4<T>&b) const
    {
        return Polygon4(vertex+b);
    }
    
    template <typename T>
    Polygon4<T>&  Polygon4<T>::operator+=(const Vector4<T>& b)
    {
        for(Vector4<T>& v : vertex)
            v += b;
        return *this;
    }
    

    template <typename T>
    Polygon4<T>   Polygon4<T>::operator-(const Vector4<T>&b) const
    {
        return Polygon4(vertex-b);
    }
    
    template <typename T>
    Polygon4<T>&  Polygon4<T>::operator-=(const Vector4<T>&b)
    {
        for(Vector4<T>& v : vertex)
            v -= b;
        return *this;
    }

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    Polygon4<product_t<T,U>> Polygon4<T>::operator*(U b) const
    {
        return Polygon4<product_t<T,U>>(vertex*b);
    }
        
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_mul_v<T,U>)
    Polygon4<T>& Polygon4<T>::operator*=(U b) 
    {
        for(Vector4<T>& v : vertex)
            v *= b;
        return *this;
    }

    template <typename T>
        template <typename U>
    Polygon2<product_t<T,U>>   Polygon4<T>::operator*(const Tensor42<U>& b) const
    {
        return Polygon2<product_t<T,U>>(vertex * b);
    }

    template <typename T>
        template <typename U>
    Polygon3<product_t<T,U>>   Polygon4<T>::operator*(const Tensor43<U>&b) const
    {
        return Polygon3<product_t<T,U>>(vertex * b);
    }

    template <typename T>
        template <typename U>
    Polygon4<product_t<T,U>>   Polygon4<T>::operator*(const Tensor44<U>&b) const
    {
        return Polygon4<product_t<T,U>>(vertex * b);
    }
    
    template <typename T>
        template <typename U>
    requires self_mul_v<T,U>
    Polygon4<T>&  Polygon4<T>::operator*=(const Tensor44<U>&b)
    {
        for(Vector4<T>& v : vertex)
            v *= b;
        return *this;
    }
    
    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    Polygon4<quotient_t<T,U>> Polygon4<T>::operator/(U b) const
    {
        return Polygon4<quotient_t<T,U>>(vertex / b);
    }
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_div_v<T,U>)
    Polygon4<T>& Polygon4<T>::operator/=(U b)
    {
        for(Vector4<T>&v : vertex)
            v /= b;
        return *this;
    }

    template <typename T>
    constexpr AxBox4<T>   Polygon4<T>::bounds() const noexcept
    {
        return AxBox4<T>(UNION, vertex);
    }

    template <typename T>
    constexpr Vector4<T>    Polygon4<T>::centroid() const noexcept
    {
        if(vertex.empty())
            return Vector4<T>(ZERO);
        if constexpr (is_floating_point_v<T>)
            return sum(vertex) / ieee754_t<T>(vertex.size());
        if constexpr (is_integer_v<T>)
            return sum(vertex) / vertex.size();
        return Vector4<T>(ZERO);
    }

    template <typename T>
    T       Polygon4<T>::perimeter() const
    {
        T   ret = zero_v<T>;
        segments([&](const Vector4<T>& a, const Vector4<T>&b){
            ret += (a-b).length();
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

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    Polygon4<product_t<T,U>> operator*(T a, const Polygon4<U>&b)
    {   
        return Polygon4<product_t<T,U>>( a*b.vertex );
    }

    template <typename T>
    AxBox4<T>   aabb(const Polygon4<T>&poly)
    {
        return poly.bounds();
    }

    template <typename T>
    Vector4<T>  centroid(const Polygon4<T>& poly)
    {
        return poly.centroid();
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
