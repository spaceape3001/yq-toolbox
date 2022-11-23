////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/AxBox2.hpp>
#include <math/AxCorners2.hpp>
#include <math/Vector2.hpp>
#include <math/Size2.hpp>

namespace yq {
    template <typename T>
    struct Rectangle2 {
        //! Component data type argument to this structure (ie, template parameter T)
        using component_type = T;

        Vector2<T>      position;
        Size2<T>        size;
        
        constexpr bool    operator==(const Rectangle2&) const noexcept = default;
    };

    YQ_IEEE754_1(Rectangle2)
//  --------------------------------------------------------
//  COMPOSITION

    YQ_NAN_1(Rectangle2, Rectangle2<T>{nan_v<Vector2<T>>, nan_v<Size2<T>>})
    YQ_ZERO_1(Rectangle2, Rectangle2<T>{zero_v<Vector2<T>>, zero_v<Size2<T>>})

//  --------------------------------------------------------
//  GETTERS

    template <typename T>
    constexpr Vector2<T>  northeast(const Rectangle2<T>& rect) noexcept
    {
        return { rect.position.x+rect.size.x, rect.position.y+rect.size.y };
    }

    template <typename T>
    constexpr Vector2<T>  northwest(const Rectangle2<T>& rect) noexcept
    {
        return { rect.position.x, rect.position.y+rect.size.y };
    }

    template <typename T>
    constexpr Vector2<T>  southeast(const Rectangle2<T>& rect) noexcept
    {
        return { rect.position.x+rect.size.x, rect.position.y };
    }

    template <typename T>
    constexpr Vector2<T>  southwest(const Rectangle2<T>& rect) noexcept
    {
        return { rect.position.x, rect.position.y };
    }


//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_NAN_1(Rectangle2, is_nan(v.position) || is_nan(v.size))

    template <typename T>
    constexpr AxBox2<T>   aabb(const Rectangle2<T>& rect) noexcept
    {
        return aabb(southwest(rect), northeast(rect));
    }

    template <typename T>
    constexpr AxCorners2<Vector2<T>>  corners(const Rectangle2<T>& v) noexcept
    {
        return { 
            southwest(v),
            northwest(v),
            southeast(v),
            northeast(v)
        };
    }

    template <typename T>
    bool is_finite(const Rectangle2<T>& v)
    {
        return is_finite(v.position) && is_finite(v.size());
    }

//  --------------------------------------------------------
//  POSITIVE


//  --------------------------------------------------------
//  NEGATIVE


//  --------------------------------------------------------
//  NORMALIZATION


//  --------------------------------------------------------
//  ADDITION


//  --------------------------------------------------------
//  SUBTRACTION


//  --------------------------------------------------------
//  MULTIPLICATION


//  --------------------------------------------------------
//  DIVISION

//  --------------------------------------------------------
//  POWERS

//  --------------------------------------------------------
//  DOT PRODUCT


//  --------------------------------------------------------
//  INNER PRODUCT


//  --------------------------------------------------------
//  OUTER PRODUCT


//  --------------------------------------------------------
//  CROSS PRODUCT


///  --------------------------------------------------------
//  OTIMES PRODUCT

//  --------------------------------------------------------
//  UNIONS

//  --------------------------------------------------------
//  INTERSECTIONS


//  --------------------------------------------------------
//  PROJECTIONS

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS



}

YQ_TYPE_DECLARE(yq::Rectangle2D)
YQ_TYPE_DECLARE(yq::Rectangle2F)
YQ_TYPE_DECLARE(yq::Rectangle2I)
YQ_TYPE_DECLARE(yq::Rectangle2U)
