////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_TRIANGLE4_HPP 1

#include <yq-toolbox/typedef/triangle4.hpp>

#include <yq-toolbox/keywords.hpp>
#include <yq-toolbox/trait/product.hpp>
#include <yq-toolbox/trait/quotient.hpp>
#include <yq-toolbox/trait/self_divide.hpp>
#include <yq-toolbox/trait/self_multiply.hpp>
#include <yq-toolbox/vector/Vector4.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq {
    struct Stream;
    
    template <typename> struct Tensor22;
    template <typename> struct Tensor23;
    template <typename> struct Tensor24;
    template <typename> struct Triangle2;
    template <typename> struct Triangle3;
    template <typename> struct TriangleData;

    /*! \brief 3D triangle
    */
    template <typename T>
    struct Triangle4 {
        //! Capture the template parameter
        using component_type    = T;
    
        //! First point
        Vector4<T>  a;

        //! Second point
        Vector4<T>  b;

        //! Third point
        Vector4<T>  c;

        //! Default constructor
        constexpr Triangle4() noexcept = default;

        //! Component wise constructor
        constexpr Triangle4(const Vector4<T>& _a, const Vector4<T>& _b, const Vector4<T>& _c) noexcept : a(_a), b(_b), c(_c) {}

        //! Constructs from segment and point
        //! 
        //! This uses the segment for the first two points, with c being the third point
        constexpr Triangle4(const Segment4<T>&, const Vector4<T>& c) noexcept;

        //! Sets ALL three to the same point value (should have no area)
        constexpr Triangle4(all_t, const Vector4<T>& v) noexcept : a(v), b(v), c(v) {}

        //! Sets all to not-a-number
        consteval Triangle4(nan_t) noexcept : Triangle4(ALL, Vector4<T>(NAN)) {}

        //! Sets all to zero
        consteval Triangle4(zero_t) noexcept : Triangle4(ALL, Vector4<T>(ZERO)) {}
        
        //! Converts to another triangle of compatible data type
        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Triangle4<U>() const noexcept
        {
            return { (Vector4<U>) a, (Vector4<U>) b, (Vector4<U>) c };
        }
        
        //! Converts to another triangle of compatible data type
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator Triangle4<U>() const 
        {
            return { (Vector4<U>) a, (Vector4<U>) b, (Vector4<U>) c };
        }

        //! Defaulted equality operator
        constexpr bool operator==(const Triangle4&) const noexcept = default;
        
        //! Implicit conversion to triangle data
        constexpr operator TriangleData<Vector4<T>> () const noexcept;

        //! Affirmation (positive) operator
        constexpr Triangle4 operator+() const noexcept;

        //! Negation
        constexpr Triangle4 operator-() const noexcept;
        
        //! Returns a triangle shifted by the given displacement
        constexpr Triangle4 operator+(const Vector4<T>&) const noexcept;

        //! Displaces this triangle
        Triangle4& operator+=(const Vector4<T>&) noexcept;

        //! Returns a triangle shifted opposite by the given displacement
        constexpr Triangle4 operator-(const Vector4<T>&) const noexcept;

        //! Displaces this triangle away by the given amount
        Triangle4& operator-=(const Vector4<T>&) noexcept;
        
        //! Returns a scaled triangle
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Triangle4<product_t<T,U>> operator*(U) const noexcept;
        
        //! Scales this triangle
        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Triangle4& operator*=(U) noexcept;

        //! Projects into two dimensions
        template <typename U>
        Triangle2<product_t<T,U>>   operator*(const Tensor42<U>&) const noexcept;

        //! Projects into three dimensions
        template <typename U>
        Triangle3<product_t<T,U>>   operator*(const Tensor43<U>&) const noexcept;

        //! Projects to another four-dimension
        template <typename U>
        Triangle4<product_t<T,U>>   operator*(const Tensor44<U>&) const noexcept;

        //! Self-projects using the tensor
        template <typename U>
        requires self_multiply_v<T,U>
        Triangle4&   operator*=(const Tensor44<U>&) noexcept;

        //! Returns a reduced triangle
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Triangle4<quotient_t<T,U>> operator/(U) const noexcept;

        //! Self-reduces this triangle
        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Triangle4& operator/=(U) noexcept;
        
        //! Area of this triangle
        square_t<T>             area() const;

        /*! \brief Bounding box for this triangle
        */
        constexpr AxBox4<T>   bounds() const noexcept;

        //! Edge opposite the "A" vertex
        constexpr Segment4<T>   edge_a() const noexcept;

        //! Length of the edge-a segment
        constexpr T             edge_a_length() const noexcept;

        //! Length² of the edge-a segment
        constexpr square_t<T>   edge_a_length²() const noexcept;

        //! Edge opposite the "B" vertex
        constexpr Segment4<T>   edge_b() const noexcept;

        //! Length of the edge-b segment
        constexpr T             edge_b_length() const noexcept;

        //! Length² of the edge-b segment
        constexpr square_t<T>   edge_b_length²() const noexcept;

        //! Edge opposite the "C" vertex
        constexpr Segment4<T>   edge_c() const noexcept;

        //! Length of the edge-c segment
        constexpr T             edge_c_length() const noexcept;

        //! Length² of the edge-c segment
        constexpr square_t<T>   edge_c_length²() const noexcept;
        
        //! Perimeter of this triangel
        //! \note Might not be reliable for non-floating point types
        T       perimeter() const;
    };

    YQ_IEEE754_1(Triangle4)
    YQ_INTEGER_1(Triangle4)
    YQ_IS_INTEGER_1(Triangle4)

//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create a triangle from three points */
    template <typename T>
    Triangle4<T>    triangle(const Vector4<T>& a, const Vector4<T>& b, const Vector4<T>& c)
    {
        return { a, b, c };
    }

    YQ_NAN_1(Triangle4, Triangle4<T>(NAN))
    YQ_ZERO_1(Triangle4, Triangle4<T>(ZERO))

//  --------------------------------------------------------
//  --------------------------------------------------------


    YQ_IS_FINITE_1(Triangle4, is_finite(v.a) && is_finite(v.b) && is_finite(v.c))
    YQ_IS_NAN_1(Triangle4, is_nan(v.a) || is_nan(v.b) || is_nan(v.c) )

    /*! \brief Scales the right triangle by the left factor */
    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Triangle4<product_t<T,U>> operator*(T lhs, const Triangle4<U>& rhs) noexcept;

    /*! \brief Creates an axially aligned bounding box from the three triangle vertices */
    template <typename T>
    constexpr AxBox4<T>   aabb(const Triangle4<T>& tri) noexcept;

    /*! \brief Computes the perimeter of the triangle
    */
    template <typename T>
    T       perimeter(const Triangle4<T>& tri);

}

YQ_TYPE_DECLARE(yq::Triangle4D)
YQ_TYPE_DECLARE(yq::Triangle4F)
YQ_TYPE_DECLARE(yq::Triangle4I)
YQ_TYPE_DECLARE(yq::Triangle4U)

