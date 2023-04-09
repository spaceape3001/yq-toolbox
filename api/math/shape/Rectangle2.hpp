////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_RECTANGLE2_HPP 1

#include <math/vector/Vector2.hpp>
#include <math/shape/Size2.hpp>

namespace yq {

    /*! \brief Rectangle in two dimensions
    */
    template <typename T>
    struct Rectangle2 {
        //! Component data type argument to this structure (ie, template parameter T)
        using component_type = T;

        //! Our position
        Vector2<T>      position;
        
        //! Our size
        Size2<T>        size;
        
        constexpr Rectangle2() noexcept = default;
        constexpr Rectangle2(const Vector2<T>& pos, const Size2<T>& sz) noexcept : position(pos), size(sz) {}
        constexpr Rectangle2(const Size2<T>&sz) noexcept : Rectangle2(Vector2<T>(ZERO), sz) {}
        constexpr Rectangle2(all_t, T v) noexcept : position(ALL, v), size(ALL, v) {}
        template <typename=void> requires has_nan_v<T>
        consteval Rectangle2(nan_t) noexcept : Rectangle2(ALL, nan_v<T>) {}
        consteval Rectangle2(zero_t) noexcept : Rectangle2(ALL, zero_v<T>) {}
        
        explicit constexpr Rectangle2(const AxBox2<T>&) noexcept;
        
        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Rectangle2<U>() const noexcept
        {
            return { (Vector2<U>) position, (Size2<U>) size };
        }
        
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator Rectangle2<U>() const 
        {
            return { (Vector2<U>) position, (Size2<U>) size };
        }

        //! Defaulted comparison operator
        constexpr bool    operator==(const Rectangle2&) const noexcept = default;

        constexpr Rectangle2    operator+() const noexcept;
        constexpr Rectangle2    operator-() const noexcept;

        constexpr Rectangle2    operator+(const Rectangle2&) const noexcept;
        Rectangle2&             operator+=(const Rectangle2&) noexcept;

        constexpr Rectangle2    operator+(const Size2<T>&) const noexcept;
        Rectangle2&             operator+=(const Size2<T>&) noexcept;

        constexpr Rectangle2    operator+(const Vector2<T>&) const noexcept;
        Rectangle2&             operator+=(const Vector2<T>&) noexcept;

        constexpr Rectangle2    operator-(const Rectangle2&) const noexcept;
        Rectangle2&             operator-=(const Rectangle2&) noexcept;

        constexpr Rectangle2    operator-(const Size2<T>&) const noexcept;
        Rectangle2&             operator-=(const Size2<T>&) noexcept;

        constexpr Rectangle2    operator-(const Vector2<T>&) const noexcept;
        Rectangle2&             operator-=(const Vector2<T>&) noexcept;
        
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Rectangle2<product_t<T,U>>  operator*(U) const noexcept;
        template <typename U>
        requires (is_arithmetic_v<U> && self_mul_v<T,U>)
        Rectangle2&  operator*=(U) noexcept;
        
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Rectangle2<quotient_t<T,U>>  operator/(U) const noexcept;
        template <typename U>
        requires (is_arithmetic_v<U> && self_div_v<T,U>)
        Rectangle2&  operator/=(U) noexcept;


        //! Our bounding box
        constexpr AxBox2<T>   bounds() const noexcept;

        //! Computes the corners
        constexpr AxCorners2<Vector2<T>>  corners() const noexcept;

        constexpr T   height() const noexcept;

        //! Computes the north east corner, returns it
        constexpr Vector2<T>  northeast() const noexcept;

        //! Computes the north west corner, returns it
        constexpr Vector2<T>  northwest() const noexcept;

        //! Computes the south east corner, returns it
        constexpr Vector2<T>  southeast() const noexcept;

        //! Computes the south west corner, returns it
        constexpr Vector2<T>  southwest() const noexcept;
        
        constexpr bool          valid() const noexcept;

        constexpr T   width() const noexcept;
    };

    YQ_INTEGER_1(Rectangle2)
    YQ_IS_INTEGER_1(Rectangle2)
    YQ_IEEE754_1(Rectangle2)

    YQ_NAN_1(Rectangle2, Rectangle2<T>{nan_v<Vector2<T>>, nan_v<Size2<T>>})
    YQ_ZERO_1(Rectangle2, Rectangle2<T>{zero_v<Vector2<T>>, zero_v<Size2<T>>})


    YQ_IS_NAN_1(Rectangle2, is_nan(v.position) || is_nan(v.size))
    YQ_IS_FINITE_1(Rectangle2, is_finite(v.position) && is_finite(v.size))

    /*! \brief Computes the bounding box of the given rectangle
    */
    template <typename T>
    constexpr AxBox2<T>   aabb(const Rectangle2<T>& rect) noexcept;
    
    /*! \brief Computes the corners of the given rectangle
    */
    template <typename T>
    constexpr AxCorners2<Vector2<T>>  corners(const Rectangle2<T>& rect) noexcept;
    
    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Rectangle2<product_t<T,U>> operator*(T, const Rectangle2<T>&) noexcept;
}

YQ_TYPE_DECLARE(yq::Rectangle2D)
YQ_TYPE_DECLARE(yq::Rectangle2F)
YQ_TYPE_DECLARE(yq::Rectangle2I)
YQ_TYPE_DECLARE(yq::Rectangle2U)
