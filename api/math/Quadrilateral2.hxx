////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once


/* 
    This is the template IMPLEMENTATION of the quadrilateral2 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <math/Quadrilateral2.hpp>
#include <math/AxBox2.hpp>
#include "QuadrilateralData.hpp"

namespace yq {
    template <typename T>
    constexpr Quadrilateral2<T>::Quadrilateral2(const AxBox2<T>&box) noexcept :
        Quadrilateral2(box.ll(), box.hl(), box.hh(), box.lh()) {}
    
    template <typename T>
    constexpr Quadrilateral2<T>::Quadrilateral2(const Rectangle2<T>&rect) noexcept :
        Quadrilateral2(rect.southwest(), rect.southeast(), rect.northeast(), rect.northwest()) {}

    template <typename T>
    constexpr Quadrilateral2<T>::operator QuadrilateralData<Vector2<T>>() const noexcept
    {
        return { a, b, c, d };
    }

    template <typename T>
    constexpr square_t<T> Quadrilateral2<T>::_area() const noexcept
    {
        return delta_area(b, a) + delta_area(c, b) + delta_area(d, c) + delta_area(a, d);
    }

    template <typename T>
    constexpr square_t<T> Quadrilateral2<T>::area() const noexcept
    {
        return middivide(abs(_area()));
    }

    template <typename T>
    constexpr AxBox2<T>   Quadrilateral2<T>::bounds() const noexcept 
    {
        return AxBox2<T>(UNION, { a, b, c, d });
    }

    template <typename T>
    constexpr bool      Quadrilateral2<T>::is_ccw() const noexcept
    {
        return _area() < zero_v<square_t<T>>;
    }

    template <typename T>
    constexpr bool      Quadrilateral2<T>::is_clockwise() const noexcept
    {
        return _area() > zero_v<square_t<T>>;
    }

    template <typename T>
    T         Quadrilateral2<T>::perimeter() const
    {
        return (b-a).length() + (c-b).length() + (d-c).length() + (a-d).length();
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T>
    Quadrilateral2<T> quadrilateral(const AxBox2<T>& ax)
    {
        return Quadrilateral2<T>(ax);
    }

    template <typename T>
    Quadrilateral2<T> quadrilateral(const Rectangle2<T>& rect)
    {
        return Quadrilateral2<T>(rect);
    }

    template <typename T>
    AxBox2<T>   aabb(const Quadrilateral2<T>& quad)
    {
        return quad.bounds();
    }

    template <typename T>
    square_t<T>    area(const Quadrilateral2<T>& quad)
    {
        return quad.area();
    }

    template <typename T>
    bool    is_ccw(const Quadrilateral2<T>& quad)
    {
        return quad.is_ccw();
    }

    template <typename T>
    T       perimeter(const Quadrilateral2<T>& quad)
    {
        return quad.perimeter();
    }
}
