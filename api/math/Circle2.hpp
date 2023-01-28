////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <math/Vector2.hpp>
#include <math/AxBox2.hpp>

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
        
        //! Equality operator (defaulted)
        constexpr bool operator==(const Circle2&) const noexcept = default;
            
        /*! \brief Computes the area of this circle
        */
        constexpr square_t<T> area() const noexcept
        {
            if constexpr ( has_ieee754_v<T> )
                return std::numbers::pi_v<ieee754_t<T>> * (radius*radius);
            else
                return {};
        }

        //! Returns the bounding box for this circle
        constexpr AxBox2<T>   bounds() const noexcept 
        {
            T       r   = abs(radius);
            return {{
                point.x - r,
                point.y - r
            },{
                point.x + r,
                point.y + r
            }};
        }
        
        /*! \brief Computes the circumference
        */
        constexpr T     circumference() const noexcept
        {
            if constexpr ( has_ieee754_v<T> )
                return ieee754_t<T>(2.) * std::numbers::pi_v<ieee754_t<T>> * radius;
            else
                return {};
        }

        /*! \brief Computes the diameter
        */
        constexpr T     diameter() const noexcept
        {
            return radius + radius;
        }

        //! TRUE if the radius is greater than zero!
        constexpr bool    valid() const noexcept
        {
            return radius >= T{};
        }
    };

    YQ_IEEE754_1(Circle2)



    YQ_NAN_1(Circle2, { nan_v<Vector2<T>>, nan_v<T> })
    YQ_ZERO_1(Circle2, { zero_v<Vector2<T>>, zero_v<T> })

    /*! \brief Creates cricle from point and radius
    */
    template <typename T>
    Circle2<T>  circle(const Vector2<T>& point, T radius)
    {
        return {point, radius};
    }

    
    YQ_IS_FINITE_1(Circle2, is_finite(v.point) && is_finite(v.radius))
    YQ_IS_NAN_1(Circle2, is_nan(v.point) || is_nan(v.radius))

    //  AxBox2D's helpers
    template <typename T>
    Circle2<T>          AxBox2<T>::circumcircle() const
    {
        return circle( center(), half_v<T>*span().length() );
    }
    
    template <typename T>
    constexpr bool        AxBox2<T>::eclipses(const Circle2<T>& b) const noexcept
    {
        return eclipses(b.bounds());
    }

    template <typename T>
    constexpr Circle2<T>  AxBox2<T>::incircle() const noexcept
    {
        return circle(center(), middivide(span().cmin()));
    }
    


    /*! \brief Bounding box for a circle
    */
    template <typename T>
    constexpr AxBox2<T>   aabb(const Circle2<T>& cir) noexcept
    {   
        return cir.bounds();
    }
    
    /*! \brief Checks for validity
    
        A valid circle is one whose radius is greater or equal to zer
    */
    template <typename T>
    constexpr bool  is_valid(const Circle2<T>&cir) noexcept
    {
        return cir.valid();
    }


    /*! \brief Computes the area of a 2D circle
    */
    template <typename T>
    constexpr square_t<T> area(const Circle2<T>& cir) noexcept
    {
        return cir.area();
    }
    
    /*! \brief Computes smallest circle containing the given box
    
        \note The resulting circle will be centered within the box
    */
    template <typename T>
    Circle2<T>    circumcircle(const AxBox2<T>& box) 
    {
        return box.circumcircle();
    }
    
    /*! \brief Computes the circumference of a circle
    */
    template <typename T>
    constexpr T     circumference(const Circle2<T>& cir) noexcept
    {
        return cir.circumference();
    }

    /*! \brief Computes the diameter of a circle
    */
    template <typename T>
    constexpr T     diameter(const Circle2<T>& cir) noexcept
    {
        return cir.diameter();
    }

    /*! \brief Computes biggest circle within the bounding box
    
        \note The resulting circle will be centered within the box
    */
    template <typename T>
    constexpr Circle2<T>    incircle(const AxBox2<T>& box) noexcept
    {
        return box.incircle();
    }

    /*! \brief Computes the perimeter (aka circumference) of a circle
    */
    template <typename T>
    constexpr T   permimeter(const Circle2<T>& cir) noexcept
    {
        return cir.circumference();
    }

}

YQ_TYPE_DECLARE(yq::Circle2D)
YQ_TYPE_DECLARE(yq::Circle2F)
YQ_TYPE_DECLARE(yq::Circle2I)
YQ_TYPE_DECLARE(yq::Circle2U)

