////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <math/Vector2.hpp>

namespace yq {

    /*! \brief Circle in two diemsnions
    */
    template <typename T>
    struct Circle2 {
    
        //! Component type (ie, the template parameter)
        using component_t   = T;

        //! Center point
        Vector2<T>  point;
        
        //! Radius
        T           radius;
        
        constexpr Circle2() noexcept = default;
        constexpr Circle2(const Vector2<T>& pt, T r) : point(pt), radius(r) {}
        constexpr Circle2(nan_t) : Circle2(Vector2<T>(NAN), nan_v<T>) {}
        constexpr Circle2(zero_t) : Circle2(Vector2<T>(ZERO), zero_v<T>) {}
        
        constexpr Circle2(focus_t, const Vector2<T>& focus, const T dist) noexcept : Circle2(focus, dist) {}
        Circle2(focus_t, const Vector2<T>& focus, const Vector2<T>& edge);
        Circle2(opposite_t, const Vector2<T>&, const Vector2<T>&);

        //! Equality operator (defaulted)
        constexpr bool operator==(const Circle2&) const noexcept = default;
            
        constexpr Circle2   operator+() const noexcept;
        constexpr Circle2   operator-() const noexcept;
        
        constexpr Circle2   operator+(const Vector2<T>&) const noexcept;
        Circle2&            operator+=(const Vector2<T>&) noexcept;
        constexpr Circle2   operator-(const Vector2<T>&) const noexcept;
        Circle2&            operator-=(const Vector2<T>&) noexcept;
        
        template <typename U>
        requires is_arithmetic_v<U>
        Circle2<product_t<T,U>> operator*(U) const noexcept;
        
        template <typename U>
        requires (is_arithmetic_v<U> && self_mul_v<T,U>)
        Circle2<T>& operator*=(U) noexcept;
            
        template <typename U>
        requires is_arithmetic_v<U>
        Circle2<quotient_t<T,U>> operator/(U) const noexcept;
        
        template <typename U>
        requires (is_arithmetic_v<U> && self_div_v<T,U>)
        Circle2<T>& operator/=(U) noexcept;

        /*! \brief Computes the area of this circle
        */
        constexpr square_t<T> area() const noexcept;

        //! Returns the bounding box for this circle
        constexpr AxBox2<T>   bounds() const noexcept;
        
        /*! \brief Computes the circumference
        */
        constexpr T     circumference() const noexcept;

        /*! \brief Computes the diameter
        */
        constexpr T     diameter() const noexcept;
        
        //! Returns a fixed copy of the circle (if it's invalid and possible to do)
        constexpr Circle2   fixed() const noexcept;

        //! TRUE if the radius is greater than zero!
        constexpr bool    valid() const noexcept;
    };

    YQ_IEEE754_1(Circle2)
    YQ_INTEGER_1(Circle2)
    YQ_IS_INTEGER_1(Circle2)



    YQ_NAN_1(Circle2, Circle2<T>(NAN))
    YQ_ZERO_1(Circle2, Circle2<T>(ZERO))

    /*! \brief Creates cricle from point and radius
    */
    template <typename T>
    Circle2<T>  circle(const Vector2<T>& point, T radius)
    {
        return {point, radius};
    }

    
    YQ_IS_FINITE_1(Circle2, is_finite(v.point) && is_finite(v.radius))
    YQ_IS_NAN_1(Circle2, is_nan(v.point) || is_nan(v.radius))

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    Circle2<product_t<T,U>> operator*(T, const Circle2<U>&);

    
    /*! \brief Bounding box for a circle
    */
    template <typename T>
    constexpr AxBox2<T>   aabb(const Circle2<T>& cir) noexcept;
    

    /*! \brief Computes the area of a 2D circle
    */
    template <typename T>
    constexpr square_t<T> area(const Circle2<T>& cir) noexcept;
    
    
    /*! \brief Computes the circumference of a circle
    */
    template <typename T>
    constexpr T     circumference(const Circle2<T>& cir) noexcept;

    /*! \brief Computes the diameter of a circle
    */
    template <typename T>
    constexpr T     diameter(const Circle2<T>& cir) noexcept;

    /*! \brief Checks for validity
    
        A valid circle is one whose radius is greater or equal to zer
    */
    template <typename T>
    constexpr bool  is_valid(const Circle2<T>&cir) noexcept;


    /*! \brief Computes the perimeter (aka circumference) of a circle
    */
    template <typename T>
    constexpr T   permimeter(const Circle2<T>& cir) noexcept;

}

YQ_TYPE_DECLARE(yq::Circle2D)
YQ_TYPE_DECLARE(yq::Circle2F)
YQ_TYPE_DECLARE(yq::Circle2I)
YQ_TYPE_DECLARE(yq::Circle2U)

