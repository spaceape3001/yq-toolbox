////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_TRIANGLE2_HPP 1

#include <math/preamble.hpp>
#include <math/Vector2.hpp>

namespace yq {

    /*! \brief 2D triangle
    */
    template <typename T>
    struct Triangle2 {
        //! Capture the template parameter
        using component_type    = T;
    
        Vector2<T>   a, b, c;
        
        constexpr Triangle2() noexcept = default;
        constexpr Triangle2(const Vector2<T>& _a, const Vector2<T>& _b, const Vector2<T>& _c) noexcept : a(_a), b(_b), c(_c) {}
        constexpr Triangle2(const Segment2<T>&, const Vector2<T>& c) noexcept;
        constexpr Triangle2(all_t, const Vector2<T>& v) noexcept : a(v), b(v), c(v) {}
        consteval Triangle2(nan_t) noexcept : Triangle2(ALL, Vector2<T>(NAN)) {}
        consteval Triangle2(zero_t) noexcept : Triangle2(ALL, Vector2<T>(ZERO)) {}
        
        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Triangle2<U>() const noexcept
        {
            return { (Vector2<U>) a, (Vector2<U>) b, (Vector2<U>) c };
        }
        
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator Triangle2<U>() const 
        {
            return { (Vector2<U>) a, (Vector2<U>) b, (Vector2<U>) c };
        }

        //! Defaulted equality operator
        constexpr bool operator==(const Triangle2&) const noexcept = default;
        
        
        //! Implicit conversion to triangle data
        constexpr operator TriangleData<Vector2<T>> () const noexcept;

        constexpr Triangle2 operator+() const noexcept;
        constexpr Triangle2 operator-() const noexcept;
        
        constexpr Triangle2 operator+(const Vector2<T>&) const noexcept;
        Triangle2& operator+=(const Vector2<T>&) noexcept;
        constexpr Triangle2 operator-(const Vector2<T>&) const noexcept;
        Triangle2& operator-=(const Vector2<T>&) noexcept;
        
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Triangle2<product_t<T,U>> operator*(U) const noexcept;
        
        template <typename U>
        requires (is_arithmetic_v<U> && self_mul_v<T,U>)
        Triangle2& operator*=(U) noexcept;

        template <typename U>
        Triangle2<product_t<T,U>>   operator*(const Tensor22<U>&) const noexcept;

        template <typename U>
        Triangle3<product_t<T,U>>   operator*(const Tensor23<U>&) const noexcept;

        template <typename U>
        Triangle4<product_t<T,U>>   operator*(const Tensor24<U>&) const noexcept;

        template <typename U>
        requires self_mul_v<T,U>
        Triangle2&   operator*=(const Tensor22<U>&) noexcept;

        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Triangle2<quotient_t<T,U>> operator/(U) const noexcept;

        template <typename U>
        requires (is_arithmetic_v<U> && self_div_v<T,U>)
        Triangle2& operator/=(U) noexcept;

        //! Area of this triangle
        constexpr square_t<T>    area() const noexcept;
        
        /*! \brief Returns the bounding box for this triangle
        */
        constexpr AxBox2<T>   bounds() const noexcept;
        
        //! Edge opposite the "A" vertex
        constexpr Segment2<T>   edge_a() const noexcept;
        constexpr T             edge_a_length() const noexcept;
        constexpr square_t<T>   edge_a_length²() const noexcept;

        //! Edge opposite the "B" vertex
        constexpr Segment2<T>   edge_b() const noexcept;
        constexpr T             edge_b_length() const noexcept;
        constexpr square_t<T>   edge_b_length²() const noexcept;

        //! Edge opposite the "C" vertex
        constexpr Segment2<T>   edge_c() const noexcept;
        constexpr T             edge_c_length() const noexcept;
        constexpr square_t<T>   edge_c_length²() const noexcept;

        //! TRUE if this triangle is wound in counter-clockwise with its points
        constexpr bool    is_ccw() const noexcept;
        
        //! TRUE if this triangle is wound in clockwise with its points
        constexpr bool      is_clockwise() const noexcept;
        
        //! Perimeter of this triangel
        //! \note Might not be reliable for non-floating point types
        T       perimeter() const;

        /*! \brief "Point area" of the points
        
            This is a helper to area and other functions, 
            simply does an "area" of the point deltas, 
            no sign correction, no scaling.
        */
        constexpr square_t<T>   _area() const noexcept;
    };

    YQ_IEEE754_1(Triangle2)
    YQ_INTEGER_1(Triangle2)
    YQ_IS_INTEGER_1(Triangle2)


//  --------------------------------------------------------
//  COMPOSITION

    YQ_NAN_1(Triangle2, Triangle2<T>(NAN))
    YQ_ZERO_1(Triangle2, Triangle2<T>(ZERO))

    /*! \brief Create a triangle from three points */
    template <typename T>
    Triangle2<T>    triangle(const Vector2<T>& a, const Vector2<T>& b, const Vector2<T>& c)
    {
        return Triangle2<T>( a, b, c );
    }


//  --------------------------------------------------------
//  --------------------------------------------------------

    YQ_IS_FINITE_1(Triangle2, is_finite(v.a) && is_finite(v.b) && is_finite(v.c))
    YQ_IS_NAN_1(Triangle2, is_nan(v.a) || is_nan(v.b) || is_nan(v.c) )

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Triangle2<product_t<T,U>> operator*(T lhs, const Triangle2<U>& rhs) noexcept;

    /*! \brief Creates an axially aligned bounding box from the three triangle vertices */
    template <typename T>
    constexpr AxBox2<T>   aabb(const Triangle2<T>& tri) noexcept;
    
    /*! \brief Computes the area of a 2D triangle
    */
    template <typename T>
    constexpr square_t<T>    area(const Triangle2<T>& tri) noexcept;

    /*! \brief TRUE if the triangle is defined in a counter-clockwise fashion
    */
    template <typename T>
    constexpr bool    is_ccw(const Triangle2<T>& tri)noexcept;
    
    /*! \brief TRUE if the triangle is defined in a clockwise fashion
    */
    template <typename T>
    constexpr bool    is_clockwise(const Triangle2<T>& tri) noexcept;

    /*! \brief Computes the perimeter of the triangle
    */
    template <typename T>
    T       perimeter(const Triangle2<T>& tri);


}

YQ_TYPE_DECLARE(yq::Triangle2D)
YQ_TYPE_DECLARE(yq::Triangle2F)
YQ_TYPE_DECLARE(yq::Triangle2I)
YQ_TYPE_DECLARE(yq::Triangle2U)

