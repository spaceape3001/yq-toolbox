////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_CIRCLE2_HPP 1

#include <yq/typedef/oval2.hpp>

#include <yq/keywords.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>
#include <yq/trait/self_divide.hpp>
#include <yq/trait/self_multiply.hpp>
#include <yq/vector/Vector2.hpp>


namespace log4cpp { class CategoryStream; }

namespace yq {

    /*! \brief Oval in two diemsnions
    
        An oval is an ellipse whose semi-major/minor axes are bound to the X/Y axes.  
    
    */
    template <typename T>
    struct Oval2 {
    
        //! Component type (ie, the template parameter)
        using component_type    = T;

        //! Center center
        Vector2<T>  center;
        
        //! Radius
        Vector2<T>  radius;
        
        //! Default constructor
        constexpr Oval2() noexcept = default;
        
        //! Component wise constructor
        constexpr Oval2(const Vector2<T>& pt, const Vector2<T>& r) : center(pt), radius(r) {}
        
        //! Constructs to NaN
        consteval Oval2(nan_k) : Oval2(Vector2<T>(NAN), Vector2<T>(NAN)) {}
        
        //! Constructs to unit oval at origin
        consteval Oval2(unit_k) : Oval2(Vector2<T>(ZERO), Vector2<T>(ONE)) {}
        
        //! Constructs to zero oval
        consteval Oval2(zero_k) : Oval2(Vector2<T>(ZERO), Vector2<T>(ZERO)) {}
        

        //! Converts to oval of compatible type
        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Oval2<U>() const noexcept
        {
            return { (Vector2<U>) center, (Vector2<U>) radius };
        }
        
        //! Converts to oval of compatible type
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator Oval2<U>() const 
        {
            return { (Vector2<U>) center, (Vector2<U>) radius };
        }

        //! Equality operator (defaulted)
        constexpr bool operator==(const Oval2&) const noexcept = default;

        //! Positive (affirmation) operator
        constexpr Oval2   operator+() const noexcept;
        
        //! Negation operator
        constexpr Oval2   operator-() const noexcept;
        
        //! Returns a oval shifted by the specified displacement
        constexpr Oval2   operator+(const Vector2<T>&) const noexcept;
        
        //! Shifts this oval by the given displacement
        Oval2&            operator+=(const Vector2<T>&) noexcept;
        
        //! Returns a oval anti-shifted by the specified displacement
        constexpr Oval2   operator-(const Vector2<T>&) const noexcept;
        
        //! Shifts this oval opposite the given displacement
        Oval2&            operator-=(const Vector2<T>&) noexcept;
        
        //! Returns a scaled oval by the given amount
        template <typename U>
        requires is_arithmetic_v<U>
        Oval2<product_t<T,U>> operator*(U) const noexcept;
        
        //! Scales THIS oval by the given amount
        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Oval2<T>& operator*=(U) noexcept;
            
        //! Returns a reduced oval by the given amount
        template <typename U>
        requires is_arithmetic_v<U>
        Oval2<quotient_t<T,U>> operator/(U) const noexcept;
        
        //! Reduces THIS oval by the given amount
        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Oval2<T>& operator/=(U) noexcept;

        /*! \brief Computes the area of this oval
        */
        constexpr square_t<T> area() const noexcept;

        //! Returns the bounding box for this oval
        constexpr AxBox2<T>   bounds() const noexcept;
        
        /*! \brief Checks if the center is inside (or touching) the oval
        */
        constexpr bool      contains(const Vector2<T>& pt) const noexcept;
        
        //! Returns a fixed copy of the oval (if it's invalid and possible to do)
        constexpr Oval2     fixed() const noexcept;

        //! TRUE if the radius is greater than zero!
        constexpr bool      valid() const noexcept;
    };

    YQ_IEEE754_1(Oval2)
    YQ_INTEGER_1(Oval2)
    YQ_IS_INTEGER_1(Oval2)



    YQ_NAN_1(Oval2, Oval2<T>(NAN))
    YQ_ZERO_1(Oval2, Oval2<T>(ZERO))

    /*! \brief Creates cricle from center and radius
    */
    template <typename T>
    Oval2<T>  oval(const Vector2<T>& center, const Vector2<T>& radius)
    {
        return {center, radius};
    }

    
    YQ_IS_FINITE_1(Oval2, is_finite(v.center) && is_finite(v.radius))
    YQ_IS_NAN_1(Oval2, is_nan(v.center) || is_nan(v.radius))

    //! Returns a oval that's the result of the left term scalaing the right oval
    template <typename T, typename U>
    requires is_arithmetic_v<T>
    Oval2<product_t<T,U>> operator*(T, const Oval2<U>&);

    
    /*! \brief Bounding box for a oval
    */
    template <typename T>
    constexpr AxBox2<T>   aabb(const Oval2<T>& cir) noexcept;
    

    /*! \brief Computes the area of a 2D oval
    */
    template <typename T>
    constexpr square_t<T> area(const Oval2<T>& cir) noexcept;
    
    /*! \brief Checks for validity
    
        A valid oval is one whose radius is greater or equal to zer
    */
    template <typename T>
    constexpr bool  is_valid(const Oval2<T>&cir) noexcept;

}

YQ_TYPE_DECLARE(yq::Oval2D)
YQ_TYPE_DECLARE(yq::Oval2F)
YQ_TYPE_DECLARE(yq::Oval2I)
YQ_TYPE_DECLARE(yq::Oval2U)

