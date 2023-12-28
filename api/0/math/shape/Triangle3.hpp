////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_TRIANGLE3_HPP 1

#include <0/math/preamble.hpp>
#include <0/math/vector/Vector3.hpp>

namespace yq {
    /*! \brief 3D triangle
    */
    template <typename T>
    struct Triangle3 {
        //! Capture the template parameter
        using component_type    = T;
    
        //! First point
        Vector3<T>  a;

        //! Second point
        Vector3<T>  b;

        //! Third point
        Vector3<T>  c;
        
        //! Default constructor
        constexpr Triangle3() noexcept = default;

        //! Component wise constructor
        constexpr Triangle3(const Vector3<T>& _a, const Vector3<T>& _b, const Vector3<T>& _c) noexcept : a(_a), b(_b), c(_c) {}

        //! Constructs from segment and point
        //! 
        //! This uses the segment for the first two points, with c being the third point
        constexpr Triangle3(const Segment3<T>&, const Vector3<T>& c) noexcept;

        //! Sets ALL three to the same point value (should have no area)
        constexpr Triangle3(all_t, const Vector3<T>& v) noexcept : a(v), b(v), c(v) {}

        //! Sets all to not-a-number
        consteval Triangle3(nan_t) noexcept : Triangle3(ALL, Vector3<T>(NAN)) {}

        //! Sets all to zero
        consteval Triangle3(zero_t) noexcept : Triangle3(ALL, Vector3<T>(ZERO)) {}

        //! Converts to another triangle of compatible data type
        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Triangle3<U>() const noexcept
        {
            return { (Vector3<U>) a, (Vector3<U>) b, (Vector3<U>) c };
        }
        
        //! Converts to another triangle of compatible data type
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator Triangle3<U>() const 
        {
            return { (Vector3<U>) a, (Vector3<U>) b, (Vector3<U>) c };
        }

        //! Defaulted equality operator
        constexpr bool operator==(const Triangle3&) const noexcept = default;
        
        //! Implicit conversion to triangle data
        constexpr operator TriangleData<Vector3<T>> () const noexcept;

        //! Affirmation (positive) operator
        constexpr Triangle3 operator+() const noexcept;

        //! Negation
        constexpr Triangle3 operator-() const noexcept;
        
        //! Returns a triangle shifted by the given displacement
        constexpr Triangle3 operator+(const Vector3<T>&) const noexcept;

        //! Displaces this triangle
        Triangle3& operator+=(const Vector3<T>&) noexcept;

        //! Returns a triangle shifted opposite by the given displacement
        constexpr Triangle3 operator-(const Vector3<T>&) const noexcept;

        //! Displaces this triangle away by the given amount
        Triangle3& operator-=(const Vector3<T>&) noexcept;
        
        //! Returns a scaled triangle
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Triangle3<product_t<T,U>> operator*(U) const noexcept;
        
        //! Scales this triangle
        template <typename U>
        requires (is_arithmetic_v<U> && self_mul_v<T,U>)
        Triangle3& operator*=(U) noexcept;

        //! Projects into two dimensions
        template <typename U>
        Triangle2<product_t<T,U>>   operator*(const Tensor32<U>&) const noexcept;

        //! Projects to another three-dimension
        template <typename U>
        Triangle3<product_t<T,U>>   operator*(const Tensor33<U>&) const noexcept;

        //! Projects into four dimensions
        template <typename U>
        Triangle4<product_t<T,U>>   operator*(const Tensor34<U>&) const noexcept;

        //! Self-projects using the tensor
        template <typename U>
        requires self_mul_v<T,U>
        Triangle3&   operator*=(const Tensor33<U>&) noexcept;

        //! Returns a reduced triangle
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Triangle3<quotient_t<T,U>> operator/(U) const noexcept;

        //! Self-reduces this triangle
        template <typename U>
        requires (is_arithmetic_v<U> && self_div_v<T,U>)
        Triangle3& operator/=(U) noexcept;
        
        //! Area of this triangle
        square_t<T>             area() const;
        
        /*! \brief Returns the bounding box for this triangle
        */
        constexpr AxBox3<T>   bounds() const noexcept;

        //! Edge opposite the "A" vertex
        constexpr Segment3<T>   edge_a() const noexcept;

        //! Length of the edge-a segment
        constexpr T             edge_a_length() const noexcept;

        //! Length² of the edge-a segment
        constexpr square_t<T>   edge_a_length²() const noexcept;

        //! Edge opposite the "B" vertex
        constexpr Segment3<T>   edge_b() const noexcept;

        //! Length of the edge-b segment
        constexpr T             edge_b_length() const noexcept;

        //! Length² of the edge-b segment
        constexpr square_t<T>   edge_b_length²() const noexcept;

        //! Edge opposite the "C" vertex
        constexpr Segment3<T>   edge_c() const noexcept;

        //! Length of the edge-c segment
        constexpr T             edge_c_length() const noexcept;

        //! Length² of the edge-c segment
        constexpr square_t<T>   edge_c_length²() const noexcept;


        //! Perimeter of this triangel
        //! \note Might not be reliable for non-floating point types
        T       perimeter() const;


        //! Creates a 2D triangle by swizzling the points on x and y
        constexpr Triangle2<T>    xy() const noexcept;

        //! Creates a 2D triangle by swizzling the points on y and z
        constexpr Triangle2<T>    yz() const noexcept;

        //! Creates a 2D triangle by swizzling the points on z and x
        constexpr Triangle2<T>    zx() const noexcept;
    };
    
    YQ_IEEE754_1(Triangle3)
    YQ_INTEGER_1(Triangle3)
    YQ_IS_INTEGER_1(Triangle3)

//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create a triangle from three points */
    template <typename T>
    Triangle3<T>    triangle(const Vector3<T>& a, const Vector3<T>& b, const Vector3<T>& c)
    {
        return Triangle3<T>( a, b, c );
    }

    YQ_NAN_1(Triangle3, Triangle3<T>(NAN))
    YQ_ZERO_1(Triangle3, Triangle3<T>(ZERO))

//  --------------------------------------------------------
//  --------------------------------------------------------

    YQ_IS_FINITE_1(Triangle3, is_finite(v.a) && is_finite(v.b) && is_finite(v.c))
    YQ_IS_NAN_1(Triangle3, is_nan(v.a) || is_nan(v.b) || is_nan(v.c) )

    /*! \brief Scales the right triangle by the given left term 
    */
    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Triangle3<product_t<T,U>> operator*(T lhs, const Triangle3<U>& rhs) noexcept;
    
    /*! \brief Creates an axially aligned bounding box from the three triangle vertices */
    template <typename T>
    constexpr AxBox3<T>   aabb(const Triangle3<T>& tri) noexcept;

    #if 0
    /*! \brief Reduces 3D triangle into 2D along xy plane */
    template <typename T>
    Triangle2<T>   xy(const Triangle3<T>& a);
    
    /*! \brief Promotes 2D triangle to 3D triangle */
    template <typename T>
    Triangle3<T>   xy(const Triangle2<T>& a, std::type_identity_t<T> z);
    #endif

    /*! \brief Computes the perimeter of the triangle
    */
    template <typename T>
    T       perimeter(const Triangle3<T>& tri);

}

YQ_TYPE_DECLARE(yq::Triangle3D)
YQ_TYPE_DECLARE(yq::Triangle3F)
YQ_TYPE_DECLARE(yq::Triangle3I)
YQ_TYPE_DECLARE(yq::Triangle3U)

