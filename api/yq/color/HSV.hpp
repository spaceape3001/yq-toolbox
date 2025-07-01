////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/MetaBinder.hpp>
#include <yq/trait/has_is_finite.hpp>
#include <yq/trait/has_nan.hpp>
#include <yq/trait/has_zero.hpp>
#include <yq/typedef/hsv.hpp>

namespace yq {

    template <typename T>
    struct HSV {
        T       hue;
        T       saturation;
        T       value;

        //! Equality operator
        constexpr bool    operator==(const HSV&) const noexcept = default;

        //! Conversion of normalized floating (scaling) HSV to integer HSV
        template <typename U>
        requires (std::is_floating_point_v<T> && std::is_integral_v<U>)
        constexpr explicit operator HSV<U>() const noexcept
        {
            static constexpr const U    mx  = std::numeric_limits<U>::max();
            static constexpr const T    half    = T(0.5);
            return { (U)((hue + half) * mx), (U)((saturation + half) * mx), (U)((value + half) * mx) };
        }
        
        //! Conversion of integer HSV to normalized floating HSV
        template <typename U>
        requires (std::is_integral_v<T> && std::is_floating_point_v<U>)
        constexpr explicit operator HSV<U>() const noexcept
        {
            static constexpr const U    mx  = U(std::numeric_limits<T>::max());
            return { U(hue) / mx, U(saturation) / mx, U(value) / mx };
        }
    };


//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Creates a color
    
        Helper function to create a HSV color where the component type is deduced from
        the first argument.
    */
    template <typename T>
    constexpr HSV<T> hsl(T h, std::type_identity_t<T> s, std::type_identity_t<T> l)
    {
        return {h,s,l};
    }
    
    YQ_NAN_1(HSV, {nan_v<T>, nan_v<T>, nan_v<T>})
    YQ_ZERO_1(HSV, {zero_v<T>, zero_v<T>, zero_v<T>})
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_NAN_1(HSV, is_nan(v.hue) || is_nan(v.saturation) || is_nan(v.value))
    YQ_IS_FINITE_1(HSV, is_finite(v.hue) && is_finite(v.saturation) && is_finite(v.value))
    
}

YQ_TYPE_DECLARE(yq::HSV3D)
YQ_TYPE_DECLARE(yq::HSV3F)
YQ_TYPE_DECLARE(yq::HSV3U8)
YQ_TYPE_DECLARE(yq::HSV3U16)
