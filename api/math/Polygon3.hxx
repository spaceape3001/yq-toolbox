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

namespace yq {
    template <typename T> Polygon3<T>::Polygon3(const std::vector<Vector3<T>>&pts) : vertex(pts) {}
    template <typename T> Polygon3<T>::Polygon3(std::vector<Vector3<T>>&& pts) : vertex(std::move(pts)) {}
    template <typename T> Polygon3<T>::Polygon3(std::initializer_list<Vector3<T>> pts) : vertex(pts) {}
    template <typename T> Polygon3<T>::Polygon3(std::span<const Vector3<T>> pts) : vertex(pts) {}

    template <typename T> Polygon3<T>::Polygon3(const Triangle3<T>& t) : Polygon3({t.a, t.b, t.c}) {}
    
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
        template <typename U>
    Polygon2<trait::product_t<T,U>>   Polygon3<T>::operator*(const Tensor32<U>& b) const
    {
        return Polygon2<trait::product_t<T,U>>(vertex * b);
    }

    template <typename T>
        template <typename U>
    Polygon3<trait::product_t<T,U>>   Polygon3<T>::operator*(const Tensor33<U>&b) const
    {
        return Polygon3<trait::product_t<T,U>>(vertex * b);
    }

    template <typename T>
        template <typename U>
    Polygon4<trait::product_t<T,U>>   Polygon3<T>::operator*(const Tensor34<U>&b) const
    {
        return Polygon4<trait::product_t<T,U>>(vertex * b);
    }
    
    template <typename T>
        template <typename U>
    requires trait::self_mul_v<T,U>
    Polygon3<T>&  Polygon3<T>::operator*=(const Tensor33<U>&b)
    {
        for(Vector3<T>& v : vertex)
            v *= b;
        return *this;
    }

    template <typename T>
    constexpr AxBox3<T>   Polygon3<T>::bounds() const noexcept
    {
        return AxBox3<T>(UNION, vertex);
    }

    template <typename T>
    T       Polygon3<T>::perimeter() const
    {
        T   ret = zero_v<T>;
        segments([&](const Segment3<T>& seg){
            ret += seg.length();
        });
        return ret;
    }
    
    template <typename T>
        template <typename Pred>
    void    Polygon3<T>::segments(Pred pred) const
    {
        if(vertex.empty())
            return ;
            
        if constexpr (std::is_invocable_v<Pred, Segment3<T>>){
            pred(Segment3<T>(vertex.back(), vertex.front));
        } else if constexpr (std::is_invocable_v<Pred, Vector3<T>, Vector3<T>>){
            pred(vertex.back(), vertex.front);
        }

        size_t n = vertex.size() - 1;
        for(size_t i=0;i<n;++i){
            if constexpr (std::is_invocable_v<Pred, Segment3<T>>){
                pred(Segment3<T>(vertex[i], vertex[i+1]));
            } else if constexpr (std::is_invocable_v<Pred, Vector3<T>, Vector3<T>>){
                pred(vertex[i], vertex[i+1]);
            }
        }
    }
    
    //! Converts the polygon to segments
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

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T>
    AxBox3<T>   aabb(const Polygon3<T>&poly)
    {
        return poly.bounds();
    }

    template <typename T>
    T       perimeter(const Polygon3<T>& poly)
    {
        return poly.perimeter();
    }


    template <typename T>
    Polygon3<T> polygon(const Triangle3<T>& tri)
    {
        return Polygon3<T>(tri);
    }

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
