////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/math/glm.hpp>
#include <yq/meta/MetaBinder.hpp>
#include <yq/trait/has_is_finite.hpp>
#include <yq/trait/has_nan.hpp>
#include <yq/trait/has_zero.hpp>
#include <yq/typedef/rgb.hpp>

namespace yq {

    template <typename T>
    struct RGBA;

    /*! \brief Simple structure for RGB color
    */
    template <typename T>
    struct RGB {
        //! Component type
        using component_type = T;
    
        //! Red data
        T   red;    
        
        //! Green data
        T   green;
        
        //! Blue data
        T   blue; 
        
        //! Equality operator
        constexpr bool    operator==(const RGB&) const noexcept = default;

        #ifdef YQ_USE_GLM
        //! Conversion to GLM
        constexpr operator glm::vec<3, T, glm::defaultp>() const noexcept
        {
            return { red, green, blue };
        }
        #endif
        
        #ifdef QCOLOR_H
        template <typename=void>
        requires std::is_same_v<T,uint8_t>
        constexpr explicit operator QColor() const noexcept
        {
            return QColor((int) red, (int) green, (int) blue);
        }
        #endif
        
        //! Conversion of normalized floating (scaling) RGB to integer RGB
        template <typename U>
        requires (std::is_floating_point_v<T> && std::is_integral_v<U>)
        constexpr explicit operator RGB<U>() const noexcept
        {
            static constexpr const U    mx  = std::numeric_limits<U>::max();
            static constexpr const T    half    = T(0.5);
            return { (U)((red + half) * mx), (U)((green + half) * mx), (U)((blue + half) * mx) };
        }
        
        //! Conversion of integer RGB to normalized floating RGB
        template <typename U>
        requires (std::is_integral_v<T> && std::is_floating_point_v<U>)
        constexpr explicit operator RGB<U>() const noexcept
        {
            static constexpr const U    mx  = U(std::numeric_limits<T>::max());
            return { U(red) / mx, U(green) / mx, U(blue) / mx };
        }

        template <typename U>
        requires (std::is_integral_v<T> && std::is_floating_point_v<U>)
        constexpr explicit operator RGBA<U>() const noexcept;
    };

//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Creates a color
    
        Helper function to create a RGB color where the component type is deduced from
        the first argument.
    */
    template <typename T>
    constexpr RGB<T> rgb(T r, std::type_identity_t<T> g, std::type_identity_t<T> b)
    {
        return {r,g,b};
    }

    #ifdef YQ_USE_GLM
    template <typename T, glm::qualifier Q>
    const RGB<T> rgb(const glm::vec<3,T,Q>& v)
    {
        return { v.r, v.g, v.b };
    }
    #endif
    
    YQ_NAN_1(RGB, {nan_v<T>, nan_v<T>, nan_v<T>})
    YQ_ZERO_1(RGB, {zero_v<T>, zero_v<T>, zero_v<T>})
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_NAN_1(RGB, is_nan(v.red) || is_nan(v.green) || is_nan(v.blue))
    YQ_IS_FINITE_1(RGB, is_finite(v.red) && is_finite(v.green) && is_finite(v.blue))
    
}

YQ_TYPE_DECLARE(yq::RGB3D)
YQ_TYPE_DECLARE(yq::RGB3F)
YQ_TYPE_DECLARE(yq::RGB3U8)
YQ_TYPE_DECLARE(yq::RGB3U16)
