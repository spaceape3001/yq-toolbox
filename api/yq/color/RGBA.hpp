////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/color/RGB.hpp>
#include <yq/math/glm.hpp>
#include <yq/meta/InfoBinder.hpp>
#include <yq/trait/has_is_finite.hpp>
#include <yq/trait/has_nan.hpp>
#include <yq/trait/has_one.hpp>
#include <yq/trait/has_zero.hpp>
#include <yq/typedef/rgba.hpp>

namespace yq {


    /*! \brief Simple structure for RGBA color data
    
        \tparam T   type of the component
    */
    template <typename T>
    struct RGBA {
        //! Component Type
        using component_type = T;
    
        //! Red data
        T   red;
        
        //! Green data
        T   green;
        
        //! Blue data
        T   blue; 
        
        //! Alpha data
        T   alpha;
        
        //! Default equality operator
        constexpr bool    operator==(const RGBA&) const noexcept = default;

        #ifdef YQ_USE_GLM
        //! Converter to GLM 
        constexpr operator glm::vec<4, T, glm::defaultp>() const noexcept
        {
            return { red, green, blue, alpha };
        }
        #endif

        #ifdef QCOLOR_H
        template <typename=void>
        requires std::is_same_v<T,uint8_t>
        constexpr explicit operator QColor() const noexcept
        {
            return QColor((int) red, (int) green, (int) blue, (int) alpha);
        }
        #endif

        //! Converts normalized float RGBA to integer
        template <typename U>
        requires (std::is_floating_point_v<T> && std::is_integral_v<U>)
        constexpr explicit operator RGBA<U>() const noexcept
        {
            static constexpr const U    mx  = std::numeric_limits<U>::max();
            static constexpr const T    half    = T(0.5);
            return { (U)((red + half) * mx), (U)((green + half) * mx), (U)((blue + half) * mx), (U)((alpha + half) * mx) };
        }
        
        //! Converts integer RGBA to normalized float
        template <typename U>
        requires (std::is_integral_v<T> && std::is_floating_point_v<U>)
        constexpr explicit operator RGBA<U>() const noexcept
        {
            static constexpr const U    mx  = U(std::numeric_limits<T>::max());
            return { U(red) / mx, U(green) / mx, U(blue) / mx, U(alpha) / mx };
        }
    };

//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Creates a color (with alpha)
    
        Helper function to create a color with alpha where the component type is deduced from
        the first argument.
    */
    template <typename T>
    constexpr RGBA<T> rgba(T r, std::type_identity_t<T> g, std::type_identity_t<T> b, std::type_identity_t<T> a)
    {
        return {r,g,b,a};
    }
    
    template <typename T>
    constexpr RGBA<T> rgba(const RGB<T>& clr, std::type_identity_t<T> a)
    {
        return {clr.red,clr.green,clr.blue,a};
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    RGBA<T> rgba(RGB<T>& clr)
    {
        return {clr.red, clr.green, clr.blue, one_v<T>};
    }

    YQ_NAN_1(RGBA, {nan_v<T>, nan_v<T>, nan_v<T>, nan_v<T>})
    YQ_ZERO_1(RGBA, {zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>})
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_NAN_1(RGBA, is_nan(v.red) || is_nan(v.green) || is_nan(v.blue) || is_nan(v.alpha))
    YQ_IS_FINITE_1(RGBA, is_finite(v.red) && is_finite(v.green) && is_finite(v.blue) && is_finite(v.alpha))

}

YQ_TYPE_DECLARE(yq::RGBA4D)
YQ_TYPE_DECLARE(yq::RGBA4F)
YQ_TYPE_DECLARE(yq::RGBA4U8)
YQ_TYPE_DECLARE(yq::RGBA4U16)
