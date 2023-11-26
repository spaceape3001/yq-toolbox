////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_QUADRILATERAL2_HPP 1

#include <math/preamble.hpp>
#include <math/vector/Vector2.hpp>

namespace yq {
    /*! \brief Quadrilateral in two dimensions
    */
    template <typename T>
    struct Quadrilateral2 {
        //! Capture the template paremater
        using component_type = T;
    
        //! First vertex
        Vector2<T>     a;
        
        //! Second vertex
        Vector2<T>     b;
        
        //! Third vertex
        Vector2<T>     c;
        
        //! Fourth vertex
        Vector2<T>     d;
        
        //! Default constructor
        constexpr Quadrilateral2() noexcept = default;
        
        //! Component wise constructor
        constexpr Quadrilateral2(const Vector2<T>& _a, const Vector2<T>& _b, const Vector2<T>& _c, const Vector2<T>& _d) :
            a(_a), b(_b), c(_c), d(_d) {}
            
        //! Construct all vector components to same value
        constexpr Quadrilateral2(all_t, T v) : a(ALL, v), b(ALL, v), c(ALL, v), d(ALL, v) {}
        
        //! Construct all points to same value
        constexpr Quadrilateral2(all_t, const Vector2<T>& v) : a(v), b(v), c(v), d(v) {}
        
        //! Constructs NaN Quad
        template <typename=void> requires has_nan_v<T>
        consteval Quadrilateral2(nan_t) noexcept : Quadrilateral2(ALL, nan_v<T>) {}
        
        //! Constructs a zero Quad
        consteval Quadrilateral2(zero_t) noexcept : Quadrilateral2(ALL, zero_v<T>) {}
        
        //! Construct from AABB
        explicit constexpr Quadrilateral2(const AxBox2<T>&) noexcept;
        
        //! Construct from Rectangle
        explicit constexpr Quadrilateral2(const Rectangle2<T>&) noexcept;
        
        //! Converts to another (compatible) quadrilateral
        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Quadrilateral2<U>() const noexcept
        {
            return Quadrilateral2<U>((Vector2<U>) a, (Vector2<U>) b, (Vector2<U>) c, (Vector2<U>) d);
        }
        
        //! Converts to another (compatible) quadrilateral
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator Quadrilateral2<U>() const 
        {
            return Quadrilateral2<U>((Vector2<U>) a, (Vector2<U>) b, (Vector2<U>) c, (Vector2<U>) d);
        }

        //! Converts to QuadrilateralData
        constexpr operator QuadrilateralData<Vector2<T>>() const noexcept;


        //! Defaulted comparison operator
        constexpr bool operator==(const Quadrilateral2&) const noexcept = default;
        
        //! Positive affirmation operator
        constexpr Quadrilateral2 operator+() const noexcept;

        //! Negation operator
        constexpr Quadrilateral2 operator-() const noexcept;
        
        //! Returns a shifted quadrilateral by the given displacement
        constexpr Quadrilateral2 operator+(const Vector2<T>&) const noexcept;

        //! Displaces this quadrilateral by the given displacement
        Quadrilateral2& operator+=(const Vector2<T>&) noexcept;
        
        //! Returns a shifted quadrilateral by the given anti-displacement
        constexpr Quadrilateral2 operator-(const Vector2<T>&) const noexcept;

        //! Displaces this quadrilateral by the given anti displacement
        Quadrilateral2& operator-=(const Vector2<T>&) noexcept;
        
        //! Returns a scaled quadrilateral by the given right hand term
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Quadrilateral2<product_t<T,U>>  operator*(U) const noexcept;

        //! Scales this quadrilateral by the given amount
        template <typename U>
        requires (is_arithmetic_v<U> && self_mul_v<T,U>)
        Quadrilateral2<T>& operator*=(U) noexcept;

        //! Projects this quadrilateral to another two dimension space
        template <typename U>
        constexpr Quadrilateral2<product_t<T,U>>  operator*(const Tensor22<U>&) const noexcept;

        //! Self-projects this quadrilateral
        template <typename U>
        requires self_mul_v<T,U>
        Quadrilateral2<T>& operator*=(const Tensor22<U>&) noexcept;


        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Quadrilateral2<quotient_t<T,U>>  operator/(U) const noexcept;

        template <typename U>
        requires (is_arithmetic_v<U> && self_div_v<T,U>)
        Quadrilateral2<T>& operator/=(U) noexcept;

        //! The point "area" (not the actual area, but a component of it)
        constexpr square_t<T>   _area() const noexcept;

        constexpr square_t<T>   area() const noexcept;

        constexpr AxBox2<T>   bounds() const noexcept;
        
        constexpr bool      is_ccw() const noexcept;
        constexpr bool      is_clockwise() const noexcept;
        T         perimeter() const;
    };

    YQ_IEEE754_1(Quadrilateral2)
    YQ_INTEGER_1(Quadrilateral2)
    YQ_IS_INTEGER_1(Quadrilateral2)

//  --------------------------------------------------------
//  COMPOSITION

    YQ_NAN_1(Quadrilateral2, { nan_v<Vector2<T>>, nan_v<Vector2<T>>, nan_v<Vector2<T>>, nan_v<Vector2<T>> })
    YQ_ZERO_1(Quadrilateral2, { zero_v<Vector2<T>>, zero_v<Vector2<T>>, zero_v<Vector2<T>>, zero_v<Vector2<T>> })

    template <typename T>
    Quadrilateral2<T> quadrilateral(const AxBox2<T>& ax);

    template <typename T>
    Quadrilateral2<T> quadrilateral(const Rectangle2<T>& ax);

    template <typename T>
    Quadrilateral2<T> quadrilateral(const Vector2<T>& a, const Vector2<T>& b, const Vector2<T>& c, const Vector2<T>& d)
    {
        return { a, b, c, d };
    }

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_FINITE_1(Quadrilateral2, is_finite(v.a) && is_finite(v.b) && is_finite(v.c) && is_finite(v.d))
    YQ_IS_NAN_1(Quadrilateral2, is_nan(v.a) || is_nan(v.b) || is_nan(v.c) || is_nan(v.d) )

    template <typename T>
    AxBox2<T>   aabb(const Quadrilateral2<T>& quad);

//  --------------------------------------------------------
//  UTILITY FUNCTIONS (FOR OTHER ADVANCED THINGS TO WORK)


//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    template <typename T, typename U>
    constexpr Quadrilateral2<product_t<T,U>> operator*(T, const Quadrilateral2<U>&) noexcept;

    /*! \brief Computes the area of a 2D quatrilateral
    */
    template <typename T>
    square_t<T>    area(const Quadrilateral2<T>& quad);

    template <typename T>
    bool    is_ccw(const Quadrilateral2<T>& quad);

    template <typename T>
    T       perimeter(const Quadrilateral2<T>& quad);

}

YQ_TYPE_DECLARE(yq::Quadrilateral2D)
YQ_TYPE_DECLARE(yq::Quadrilateral2F)
YQ_TYPE_DECLARE(yq::Quadrilateral2I)
YQ_TYPE_DECLARE(yq::Quadrilateral2U)

