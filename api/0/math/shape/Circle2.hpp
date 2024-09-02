////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_CIRCLE2_HPP 1
#include <0/math/preamble.hpp>
#include <0/math/vector/Vector2.hpp>

#include <yq/keywords.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>
#include <yq/trait/self_divide.hpp>
#include <yq/trait/self_multiply.hpp>

namespace yq {

    /*! \brief Circle in two diemsnions
    */
    template <typename T>
    struct Circle2 {
    
        //! Component type (ie, the template parameter)
        using component_t   = T;

        //! Center center
        Vector2<T>  center;
        
        //! Radius
        T           radius;
        
        //! Default constructor
        constexpr Circle2() noexcept = default;
        
        //! Component wise constructor
        constexpr Circle2(const Vector2<T>& pt, T r) : center(pt), radius(r) {}
        
        //! Constructs to NaN
        consteval Circle2(nan_t) : Circle2(Vector2<T>(NAN), nan_v<T>) {}
        
        //! Constructs to unit circle at origin
        consteval Circle2(unit_t) : Circle2(Vector2<T>(ZERO), one_v<T>) {}
        
        //! Constructs to zero circle
        consteval Circle2(zero_t) : Circle2(Vector2<T>(ZERO), zero_v<T>) {}
        
        //! Constructs to focus and radius
        constexpr Circle2(focus_t, const Vector2<T>& focus, const T dist) noexcept : Circle2(focus, dist) {}
        
        //! Constructs to focus and edge
        Circle2(focus_t, const Vector2<T>& focus, const Vector2<T>& edge);
        
        //! Constructs between two opposite points
        Circle2(opposite_t, const Vector2<T>&, const Vector2<T>&);

        //! Converts to circle of compatible type
        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Circle2<U>() const noexcept
        {
            return { (Vector2<U>) center, (U) radius };
        }
        
        //! Converts to circle of compatible type
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator Circle2<U>() const 
        {
            return { (Vector2<U>) center, (U) radius };
        }

        //! Equality operator (defaulted)
        constexpr bool operator==(const Circle2&) const noexcept = default;

        //! Positive (affirmation) operator
        constexpr Circle2   operator+() const noexcept;
        
        //! Negation operator
        constexpr Circle2   operator-() const noexcept;
        
        //! Returns a circle shifted by the specified displacement
        constexpr Circle2   operator+(const Vector2<T>&) const noexcept;
        
        //! Shifts this circle by the given displacement
        Circle2&            operator+=(const Vector2<T>&) noexcept;
        
        //! Returns a circle anti-shifted by the specified displacement
        constexpr Circle2   operator-(const Vector2<T>&) const noexcept;
        
        //! Shifts this circle opposite the given displacement
        Circle2&            operator-=(const Vector2<T>&) noexcept;
        
        //! Returns a scaled circle by the given amount
        template <typename U>
        requires is_arithmetic_v<U>
        Circle2<product_t<T,U>> operator*(U) const noexcept;
        
        //! Scales THIS circle by the given amount
        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Circle2<T>& operator*=(U) noexcept;
            
        //! Returns a reduced circle by the given amount
        template <typename U>
        requires is_arithmetic_v<U>
        Circle2<quotient_t<T,U>> operator/(U) const noexcept;
        
        //! Reduces THIS circle by the given amount
        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Circle2<T>& operator/=(U) noexcept;

        /*! \brief Computes the area of this circle
        */
        constexpr square_t<T> area() const noexcept;

        //! Returns the bounding box for this circle
        constexpr AxBox2<T>   bounds() const noexcept;
        
        /*! \brief Computes the circumference
        */
        constexpr T         circumference() const noexcept;

        /*! \brief Checks if the center is inside (or touching) the circle
        */
        constexpr bool      contains(const Vector2<T>& pt) const noexcept;
        
        /*! \brief Computes the diameter
        */
        constexpr T         diameter() const noexcept;
        
        //! Returns a fixed copy of the circle (if it's invalid and possible to do)
        constexpr Circle2   fixed() const noexcept;

        //! TRUE if the radius is greater than zero!
        constexpr bool      valid() const noexcept;
    };

    YQ_IEEE754_1(Circle2)
    YQ_INTEGER_1(Circle2)
    YQ_IS_INTEGER_1(Circle2)



    YQ_NAN_1(Circle2, Circle2<T>(NAN))
    YQ_ZERO_1(Circle2, Circle2<T>(ZERO))

    /*! \brief Creates cricle from center and radius
    */
    template <typename T>
    Circle2<T>  circle(const Vector2<T>& center, T radius)
    {
        return {center, radius};
    }

    
    YQ_IS_FINITE_1(Circle2, is_finite(v.center) && is_finite(v.radius))
    YQ_IS_NAN_1(Circle2, is_nan(v.center) || is_nan(v.radius))

    //! Returns a circle that's the result of the left term scalaing the right circle
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

