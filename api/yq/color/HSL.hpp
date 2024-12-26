////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/InfoBinder.hpp>
#include <yq/trait/has_is_finite.hpp>
#include <yq/trait/has_nan.hpp>
#include <yq/trait/has_zero.hpp>
#include <yq/typedef/hsl.hpp>

#include <limits>
#include <type_traits>

namespace yq {

    template <typename T>
    struct HSL {
        T       hue;
        T       saturation;
        T       lightness;

        //! Equality operator
        constexpr bool    operator==(const HSL&) const noexcept = default;

        //! Conversion of normalized floating (scaling) HSL to integer HSL
        template <typename U>
        requires (std::is_floating_point_v<T> && std::is_integral_v<U>)
        constexpr explicit operator HSL<U>() const noexcept
        {
            static constexpr const U    mx  = std::numeric_limits<U>::max();
            static constexpr const T    half    = T(0.5);
            return { (U)((hue + half) * mx), (U)((saturation + half) * mx), (U)((lightness + half) * mx) };
        }
        
        //! Conversion of integer HSL to normalized floating HSL
        template <typename U>
        requires (std::is_integral_v<T> && std::is_floating_point_v<U>)
        constexpr explicit operator HSL<U>() const noexcept
        {
            static constexpr const U    mx  = U(std::numeric_limits<T>::max());
            return { U(hue) / mx, U(saturation) / mx, U(lightness) / mx };
        }
    };


//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Creates a color
    
        Helper function to create a HSL color where the component type is deduced from
        the first argument.
    */
    template <typename T>
    constexpr HSL<T> hsl(T h, std::type_identity_k<T> s, std::type_identity_k<T> l)
    {
        return {h,s,l};
    }
    
    YQ_NAN_1(HSL, {nan_v<T>, nan_v<T>, nan_v<T>})
    YQ_ZERO_1(HSL, {zero_v<T>, zero_v<T>, zero_v<T>})
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_NAN_1(HSL, is_nan(v.hue) || is_nan(v.saturation) || is_nan(v.lightness))
    YQ_IS_FINITE_1(HSL, is_finite(v.hue) && is_finite(v.saturation) && is_finite(v.lightness))
    
}

YQ_TYPE_DECLARE(yq::HSL3D)
YQ_TYPE_DECLARE(yq::HSL3F)
YQ_TYPE_DECLARE(yq::HSL3U8)
YQ_TYPE_DECLARE(yq::HSL3U16)
