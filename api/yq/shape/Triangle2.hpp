////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_TRIANGLE2_HPP 1


#include <yq/vector/Vector2.hpp>

#include <yq/keywords.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>
#include <yq/trait/self_divide.hpp>
#include <yq/trait/self_multiply.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq {

    /*! \brief 2D triangle
    */
    template <typename T>
    struct Triangle2 {
        //! Capture the template parameter
        using component_type    = T;
    
        //! First point
        Vector2<T>  a;

        //! Second point
        Vector2<T>  b;

        //! Third point
        Vector2<T>  c;
        
        //! Default constructor
        constexpr Triangle2() noexcept = default;
        
        //! Component wise constructor
        constexpr Triangle2(const Vector2<T>& _a, const Vector2<T>& _b, const Vector2<T>& _c) noexcept : a(_a), b(_b), c(_c) {}
        
        //! Constructs from segment and point
        //! 
        //! This uses the segment for the first two points, with c being the third point
        constexpr Triangle2(const Segment2<T>&, const Vector2<T>& c) noexcept;
        
        //! Sets ALL three to the same point value (should have no area)
        constexpr Triangle2(all_t, const Vector2<T>& v) noexcept : a(v), b(v), c(v) {}
        
        //! Sets all to not-a-number
        consteval Triangle2(nan_t) noexcept : Triangle2(ALL, Vector2<T>(NAN)) {}
        
        //! Sets all to zero
        consteval Triangle2(zero_t) noexcept : Triangle2(ALL, Vector2<T>(ZERO)) {}
        
        //! Converts to another triangle of compatible data type
        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Triangle2<U>() const noexcept
        {
            return { (Vector2<U>) a, (Vector2<U>) b, (Vector2<U>) c };
        }
        
        //! Converts to another triangle of compatible data type
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

        //! Affirmation (positive) operator
        constexpr Triangle2 operator+() const noexcept;
        
        //! Negation
        constexpr Triangle2 operator-() const noexcept;
        
        //! Returns a triangle shifted by the given displacement
        constexpr Triangle2 operator+(const Vector2<T>&) const noexcept;
        
        //! Displaces this triangle
        Triangle2& operator+=(const Vector2<T>&) noexcept;
        
        //! Returns a triangle shifted opposite by the given displacement
        constexpr Triangle2 operator-(const Vector2<T>&) const noexcept;
        
        //! Displaces this triangle away by the given amount
        Triangle2& operator-=(const Vector2<T>&) noexcept;
        
        //! Returns a scaled triangle
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Triangle2<product_t<T,U>> operator*(U) const noexcept;
        
        //! Scales this triangle
        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Triangle2& operator*=(U) noexcept;

        //! Projects to another two-dimension
        template <typename U>
        Triangle2<product_t<T,U>>   operator*(const Tensor22<U>&) const noexcept;

        //! Projects into three dimensions
        template <typename U>
        Triangle3<product_t<T,U>>   operator*(const Tensor23<U>&) const noexcept;

        //! Projects into four dimensions
        template <typename U>
        Triangle4<product_t<T,U>>   operator*(const Tensor24<U>&) const noexcept;

        //! Self-projects using the tensor
        template <typename U>
        requires self_multiply_v<T,U>
        Triangle2&   operator*=(const Tensor22<U>&) noexcept;

        //! Returns a reduced triangle
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Triangle2<quotient_t<T,U>> operator/(U) const noexcept;

        //! Self-reduces this triangle
        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Triangle2& operator/=(U) noexcept;

        //! Area of this triangle
        constexpr square_t<T>    area() const noexcept;
        
        /*! \brief Returns the bounding box for this triangle
        */
        constexpr AxBox2<T>   bounds() const noexcept;
        
        //! Edge opposite the "A" vertex
        constexpr Segment2<T>   edge_a() const noexcept;
        
        //! Length of the edge-a segment
        constexpr T             edge_a_length() const noexcept;
        
        //! Length² of the edge-a segment
        constexpr square_t<T>   edge_a_length²() const noexcept;

        //! Edge opposite the "B" vertex
        constexpr Segment2<T>   edge_b() const noexcept;

        //! Length of the edge-b segment
        constexpr T             edge_b_length() const noexcept;

        //! Length² of the edge-b segment
        constexpr square_t<T>   edge_b_length²() const noexcept;

        //! Edge opposite the "C" vertex
        constexpr Segment2<T>   edge_c() const noexcept;

        //! Length of the edge-c segment
        constexpr T             edge_c_length() const noexcept;

        //! Length² of the edge-c segment
        constexpr square_t<T>   edge_c_length²() const noexcept;

        //! TRUE if this triangle is wound in counter-clockwise with its points
        constexpr bool    is_ccw() const noexcept;
        
        //! TRUE if this triangle is wound in clockwise with its points
        constexpr bool      is_clockwise() const noexcept;
        
        //! Perimeter of this triangle
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

    /*! \brief Scales the right triangle by the given left term 
    */
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

