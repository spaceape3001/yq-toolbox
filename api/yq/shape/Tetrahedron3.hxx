////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/shape/Tetrahedron3.hpp>
#include <yq/shape/TetrahedronData.hpp>
#include <yq/trait/is_floating_point.hpp>

/* 
    This is the template IMPLEMENTATION of the tetrahedron3 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

namespace yq {
    template <typename T>
        template <typename>
    requires has_sqrt_v<square_t<T>>
    const Tetrahedron3<T>&  Tetrahedron3<T>::unit()
    {
        static const Tetrahedron3 ret(UNIT);
        return ret;
    }
    
////////////////////////////////////////////////////////////////////////////////

    #ifdef YQ_MATH_TRIANGLE3_HPP
    template <typename T>
    constexpr Tetrahedron3<T>::Tetrahedron3(const Triangle3<T>& _t, const Vector3<T>& _d) : 
        a(_t.a), b(_t.b), c(_t.c), d(_d) {}
    #endif
    
    template <typename T>
        template <typename>
    requires has_sqrt_v<square_t<T>>
    Tetrahedron3<T>::Tetrahedron3(unit_t)
    {
        //  formula taken from https://en.wikipedia.org/wiki/Tetrahedron
        const T third    = T(1./3.);
        const T sq29    = sqrt(square_t<T>(2./9.));
        const T sq89    = sqrt(square_t<T>(8./9.));
        const T sq23    = sqrt(square_t<T>(2./2.));
        
        a = { sq89, T(0.), -third };
        b = { -sq29, sq23, -third };
        c = { -sq29, -sq23, -third };
        d = { T(0.), T(0.), T(1.) };
    }

    template <typename T>
    constexpr Tetrahedron3<T>::operator TetrahedronData<Vector3<T>> () const noexcept 
    { 
        return TetrahedronData<Vector3<T>>( a, b, c, d ); 
    }
    

    template <typename T>
    constexpr Tetrahedron3<T> Tetrahedron3<T>::operator+() const noexcept
    {
        return *this;
    }

    template <typename T>
    constexpr Tetrahedron3<T> Tetrahedron3<T>::operator-() const noexcept
    {
        return Tetrahedron3(-a,-b,-c, -d);
    }
    
    template <typename T>
    constexpr Tetrahedron3<T> Tetrahedron3<T>::operator+(const Vector3<T>&rhs) const noexcept
    {
        return Tetrahedron3(a+rhs, b+rhs, c+rhs, d+rhs);
    }

    template <typename T>
    Tetrahedron3<T>& Tetrahedron3<T>::operator+=(const Vector3<T>&rhs) noexcept
    {
        a += rhs;
        b += rhs;
        c += rhs;
        d += rhs;
        return *this;
    }
    

    template <typename T>
    constexpr Tetrahedron3<T> Tetrahedron3<T>::operator-(const Vector3<T>&rhs) const noexcept
    {
        return Tetrahedron3(a-rhs, b-rhs, c-rhs, d-rhs);
    }

    template <typename T>
    Tetrahedron3<T>& Tetrahedron3<T>::operator-=(const Vector3<T>&rhs) noexcept
    {
        a -= rhs;
        b -= rhs;
        c -= rhs;
        d -= rhs;
        return *this;
    }
    
    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Tetrahedron3<product_t<T,U>> Tetrahedron3<T>::operator*(U rhs) const noexcept
    {
        return Tetrahedron3<product_t<T,U>>( a*rhs, b*rhs, c*rhs, d*rhs );
    }
    
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
    Tetrahedron3<T>& Tetrahedron3<T>::operator*=(U rhs) noexcept
    {
        a *= rhs;
        b *= rhs;
        c *= rhs;
        d *= rhs;
        return *this;
    }


    #ifdef YQ_MATH_TENSOR_3_3_HPP
    template <typename T>
        template <typename U>
    Tetrahedron3<product_t<T,U>>   Tetrahedron3<T>::operator*(const Tensor33<U>&rhs) const noexcept
    {
        return Tetrahedron3<product_t<T,U>>(a*rhs, b*rhs, c*rhs, d*rhs);
    }
    #endif

    #ifdef YQ_MATH_TENSOR_3_3_HPP
    template <typename T>
        template <typename U>
    requires self_multiply_v<T,U>
    Tetrahedron3<T>&   Tetrahedron3<T>::operator*=(const Tensor33<U>&rhs) noexcept
    {
        a *= rhs;
        b *= rhs;
        c *= rhs;
        d *= rhs;
        return *this;
    }
    #endif

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Tetrahedron3<quotient_t<T,U>> Tetrahedron3<T>::operator/(U rhs) const noexcept
    {
        return Tetrahedron3<quotient_t<T,U>>(a/rhs, b/rhs, c/rhs, d/rhs);
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_divide_v<T,U>)
    Tetrahedron3<T>& Tetrahedron3<T>::operator/=(U rhs) noexcept
    {
        a /= rhs;
        b /= rhs;
        c /= rhs;
        d /= rhs;
        return *this;
    }

    #ifdef YQ_MATH_AXBOX3_HPP
    template <typename T>
    constexpr AxBox3<T>   Tetrahedron3<T>::bounds() const noexcept
    {
        return AxBox3<T>(UNION, { a, b, c, d });
    }
    #endif

        //! Computes the centroid of the tetrahedron
    template <typename T>
    constexpr Vector3<T>    Tetrahedron3<T>::centroid() const noexcept
    {
        if constexpr (is_floating_point_v<T>)
            return ((a+b)+(c+d)) * T(0.25);
        if constexpr (is_integer_v<T>)
            return ((a+b)+(c+d)) / T(4);
        return {};
    }
        
    template <typename T>
    constexpr cube_t<T>   Tetrahedron3<T>::volume() const noexcept
    {
        return abs((a-d) DOT ((b-d) CROSS (c-d))) / ieee754_t<T>(6.);
    }

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Tetrahedron3<product_t<T,U>> operator*(T lhs, const Tetrahedron3<U>& rhs) noexcept
    {
        return Tetrahedron3<product_t<T,U>>(lhs*rhs.a, lhs*rhs.b, lhs*rhs.c, lhs*rhs.d);
    }

    #ifdef YQ_MATH_AXBOX3_HPP
    template <typename T>
    constexpr AxBox3<T>   aabb(const Tetrahedron3<T>& tri) noexcept
    {
        return tri.bounds();
    }
    #endif

    template <typename T>
    constexpr Vector3<T>  centroid(const Tetrahedron3<T>& tetra) noexcept
    {
        return tetra.centroid();
    }

    //! Computes the volume of the given tetrahedron
    template <typename T>
    constexpr cube_t<T>   volume(const Tetrahedron3<T>& tetra) noexcept
    {
        return tetra.volume();
    }
}
