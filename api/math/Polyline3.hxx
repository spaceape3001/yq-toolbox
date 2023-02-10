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

#include <math/Polyline3.hpp>
#include <math/Segment3.hpp>

namespace yq {
    template <typename T> Polyline3<T>::Polyline3(const std::vector<Vector3<T>>&pts) : vertex(pts) {}
    template <typename T> Polyline3<T>::Polyline3(std::vector<Vector3<T>>&& pts) : vertex(std::move(pts)) {}
    template <typename T> Polyline3<T>::Polyline3(std::initializer_list<Vector3<T>> pts) : vertex(pts) {}
    template <typename T> Polyline3<T>::Polyline3(const Segment3<T>&s) : Polyline3({s.a, s.b}) {}

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
        template <typename U>
    Polyline2<trait::product_t<T,U>>   Polyline3<T>::operator*(const Tensor32<U>& b) const
    {
        return Polyline2<trait::product_t<T,U>>(vertex * b);
    }

    template <typename T>
        template <typename U>
    Polyline3<trait::product_t<T,U>>   Polyline3<T>::operator*(const Tensor33<U>&b) const
    {
        return Polyline3<trait::product_t<T,U>>(vertex * b);
    }

    template <typename T>
        template <typename U>
    Polyline4<trait::product_t<T,U>>   Polyline3<T>::operator*(const Tensor34<U>&b) const
    {
        return Polyline4<trait::product_t<T,U>>(vertex * b);
    }
    
    template <typename T>
        template <typename U>
    requires trait::self_mul_v<T,U>
    Polyline3<T>&  Polyline3<T>::operator*=(const Tensor33<U>&b)
    {
        for(Vector3<T>& v : vertex)
            v *= b;
        return *this;
    }

    template <typename T>
    constexpr AxBox3<T>   Polyline3<T>::bounds() const noexcept
    {
        if(vertex.empty())
            return nan_v<AxBox3<T>>;
        return AxBox3<T>(UNION, vertex);
    }

    template <typename T>
    T       Polyline3<T>::length() const
    {
        T   ret = zero_v<T>;
        segments([&](const Segment3<T>& seg){
            ret += seg.length();
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
            if constexpr (std::is_invocable_v<Pred, Segment3<T>>){
                pred(Segment3<T>(vertex[i], vertex[i+1]));
            } else if constexpr (std::is_invocable_v<Pred, Vector3<T>, Vector3<T>>){
                pred(vertex[i], vertex[i+1]);
            }
        }
    }

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

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T>
    AxBox3<T>   aabb(const Polyline3<T>&poly)
    {
        return poly.bounds();
    }

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

    template <typename T>
    Polyline3<T> polyline(const Segment3<T>&seg)
    {
        return Polyline3<T>(seg);
    }
}
