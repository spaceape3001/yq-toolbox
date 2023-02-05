////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <math/Vector3.hpp>

namespace yq {
    /*! \brief 3D triangle
    */
    template <typename T>
    struct Triangle3 {
        //! Capture the template parameter
        using component_type    = T;
    
        Vector3<T>   a, b, c;
        
        constexpr Triangle3() noexcept = default;
        constexpr Triangle3(const Vector3<T>& _a, const Vector3<T>& _b, const Vector3<T>& _c) noexcept : a(_a), b(_b), c(_c) {}
        constexpr Triangle3(const Segment3<T>&, const Vector3<T>& c) noexcept;
        constexpr Triangle3(all_t, const Vector3<T>& v) noexcept : a(v), b(v), c(v) {}
        consteval Triangle3(nan_t) noexcept : Triangle3(ALL, Vector3<T>(NAN)) {}
        consteval Triangle3(zero_t) noexcept : Triangle3(ALL, Vector3<T>(ZERO)) {}

        //! Defaulted equality operator
        constexpr bool operator==(const Triangle3&) const noexcept = default;
        
        //! Implicit conversion to triangle data
        constexpr operator TriangleData<Vector3<T>> () const noexcept;

        constexpr Triangle3 operator+() const noexcept;
        constexpr Triangle3 operator-() const noexcept;
        
        constexpr Triangle3 operator+(const Vector3<T>&) const noexcept;
        Triangle3& operator+=(const Vector3<T>&) noexcept;
        constexpr Triangle3 operator-(const Vector3<T>&) const noexcept;
        Triangle3& operator-=(const Vector3<T>&) noexcept;
        
        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Triangle3<product_t<T,U>> operator*(U) const noexcept;
        
        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
        Triangle3& operator*=(U) noexcept;

        template <typename U>
        Triangle2<product_t<T,U>>   operator*(const Tensor32<U>&) const noexcept;

        template <typename U>
        Triangle3<product_t<T,U>>   operator*(const Tensor33<U>&) const noexcept;

        template <typename U>
        Triangle4<product_t<T,U>>   operator*(const Tensor34<U>&) const noexcept;

        template <typename U>
        requires trait::self_mul_v<T,U>
        Triangle3&   operator*=(const Tensor33<U>&) noexcept;

        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Triangle3<quotient_t<T,U>> operator/(U) const noexcept;

        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
        Triangle3& operator/=(U) noexcept;
        
        /*! \brief Returns the bounding box for this triangle
        */
        constexpr AxBox3<T>   bounds() const noexcept;

        //! Edge opposite the "A" vertex
        constexpr Segment3<T>   edge_a() const noexcept;
        constexpr T             edge_a_length() const noexcept;
        constexpr square_t<T>   edge_a_length²() const noexcept;

        //! Edge opposite the "B" vertex
        constexpr Segment3<T>   edge_b() const noexcept;
        constexpr T             edge_b_length() const noexcept;
        constexpr square_t<T>   edge_b_length²() const noexcept;

        //! Edge opposite the "C" vertex
        constexpr Segment3<T>   edge_c() const noexcept;
        constexpr T             edge_c_length() const noexcept;
        constexpr square_t<T>   edge_c_length²() const noexcept;


        //! Perimeter of this triangel
        //! \note Might not be reliable for non-floating point types
        T       perimeter() const;

        constexpr Triangle2<T>    xy() const noexcept;
        constexpr Triangle2<T>    yz() const noexcept;
        constexpr Triangle2<T>    zx() const noexcept;
    };
    
    YQ_IEEE754_1(Triangle3)

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

    template <typename T, typename U>
    requires trait::is_arithmetic_v<T>
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

