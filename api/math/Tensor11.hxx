////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the tensor11 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <math/Tensor11.hpp>
#include <math/Tensor12.hpp>
#include <math/Tensor13.hpp>
#include <math/Tensor14.hpp>

#include <math/Vector1.hpp>

namespace yq {
    template <typename T>
    constexpr Tensor11<T>  Tensor11<T>::operator-() const noexcept
    {
        return Tensor11(
            -xx
        );
    }

    template <typename T>
    constexpr Tensor11<T>   Tensor11<T>::operator+ (const Tensor11 &b) const noexcept
    {
        return Tensor11(
            xx+b.xx
        );
    }

    template <typename T>
    Tensor11<T>&   Tensor11<T>::operator+=(const Tensor11 &b) 
    {
        xx+=b.xx;
        return *this;
    }

    template <typename T>
    constexpr Tensor11<T>   Tensor11<T>::operator- (const Tensor11 &b) const noexcept
    {
        return Tensor11(
            xx-b.xx
        );
    }
    
    template <typename T>
    Tensor11<T>&   Tensor11<T>::operator-=(const Tensor11 &b) 
    {
        xx-=b.xx;
        return *this;
    }

    template <typename T>
        template <typename U>
    requires trait::is_arithmetic_v<U>
    constexpr Tensor11<product_t<T,U>>  Tensor11<T>::operator*(U b) const noexcept
    {
        return Tensor11<product_t<T,U>>(
            xx*b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Tensor11<product_t<T,U>>  Tensor11<T>::operator*=(U b) noexcept
    {
        xx*=b;        
        return *this;
    }

    template <typename T>
        template <typename U>
    constexpr Tensor11<product_t<T,U>> Tensor11<T>::operator*(const Tensor11<U>& b) const noexcept
    {
        return Tensor11<product_t<T,U>>(
            xx*b.xx
        );
    }
    
    template <typename T>
        template <typename U>
    requires trait::self_mul_v<T,U>
    Tensor11<T>& Tensor11<T>::operator*=(const Tensor11<U>& b) const noexcept
    {
        *this = *this * b;
        return *this;
    }

    template <typename T>
        template <typename U>
    constexpr Tensor12<product_t<T,U>> Tensor11<T>::operator*(const Tensor12<U>& b) const noexcept
    {
        return Tensor12<product_t<T,U>>(
            xx*b.xx,
            xx*b.xy
        );
    }
    
    template <typename T>
        template <typename U>
    constexpr Tensor13<product_t<T,U>> Tensor11<T>::operator*(const Tensor13<U>& b) const noexcept
    {
        return Tensor13<product_t<T,U>>(
            xx*b.xx,
            xx*b.xy,
            xx*b.xz
        );
    }
    
    template <typename T>
        template <typename U>
    constexpr Tensor14<product_t<T,U>> Tensor11<T>::operator*(const Tensor14<U>& b) const noexcept
    {
        return Tensor14<product_t<T,U>>(
            xx*b.xx,
            xx*b.xy,
            xx*b.xz,
            xx*b.xw
        );
    }

        
    template <typename T>
        template <typename U>
    constexpr Vector1<product_t<T,U>> Tensor11<T>::operator*(const Vector1<U>&b) const noexcept
    {
        return Vector1<product_t<T,U>>(
            xx*b.x
        );
    }


        //! Returns the determinant
    template <typename T>
    constexpr T Tensor11<T>::determinant() const noexcept
    {
        return xx;
    }

    //! Gets the diagonal as a vector
    template <typename T>
    constexpr Vector1<T>  Tensor11<T>::diagonal() const noexcept
    {
        return Vector1<T>(xx);
    }

    //! Sets the diagonal
    template <typename T>
    Tensor11<T>&   Tensor11<T>::diagonal(const Vector1<T>& v)
    {        
        xx = v.x;
        return *this;
    }

    template <typename T>
    Tensor11<T>&   Tensor11<T>::diagonal(T _xx)
    {        
        xx = _xx;
        return *this;
    }

        //! Returns the trace
    template <typename T>
    constexpr T     Tensor11<T>::trace() const noexcept
    {
        return xx;
    }

    //! Transpose, which is itself for a 1x1
    template <typename T>
    constexpr Tensor11<T> Tensor11<T>::transpose() const 
    { 
        return Tensor11( xx ); 
    }

    //! Gets the x-column as a vector
    template <typename T>
    constexpr Vector1<T>  Tensor11<T>::x_column()  const noexcept
    {
        return Vector1<T>(xx);
    }

    template <typename T>
    Tensor11<T>&   Tensor11<T>::x_column(const Vector1<T>& v)
    {
        xx = v.x;
        return *this;
    }

    //! Sets the x-column
    template <typename T>
    Tensor11<T>& Tensor11<T>::x_column(T _xx)
    {
        xx = _xx;
        return *this;
    }

    //! Gets the x-row as a vector
    template <typename T>
    constexpr Vector1<T>  Tensor11<T>::x_row() const noexcept
    {
        return Vector1<T>(xx);
    }

    //! Sets the x-row
    template <typename T>
    Tensor11<T>& Tensor11<T>::x_row(const Vector1<T>& v)
    {
        xx = v.x;
        return *this;
    }

    //! Sets the x-row
    template <typename T>
    Tensor11<T>& Tensor11<T>::x_row(T _xx)
    {
        xx = _xx;
        return *this;
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


    template <typename T, typename U>
    requires trait::is_arithmetic_v<T>
    constexpr Tensor11<product_t<T,U>>  operator*(T a, const Tensor11<U>& b)
    {
        return Tensor11<product_t<T,U>>(
            a*b.xx
        );
    }
    
    template <typename T>
    constexpr Vector1<T>  diagonal(const Tensor11<T>& v)
    {
        return v.diagonal();
    }

    template <typename T>
    constexpr Tensor11<T>  transpose(const Tensor11<T>&v)
    {
        return v.transpose();
    }


    template <typename T>
    constexpr Vector1<T>  x_column(const Tensor11<T>&v) 
    {
        return v.x_column();
    }

    template <typename T>
    constexpr Vector1<T>  x_row(const Tensor11<T>&v)
    {
        return v.x_row();
    }

}
