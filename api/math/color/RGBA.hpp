////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <math/color/RGB.hpp>

namespace yq {


    /*! \brief Simple structure for RGBA color data
    
        \tparam T   type of the component
    */
    template <typename T>
    struct RGBA {
        using component_type = T;
    
        T   red;        //!< Red data
        T   green;      //!< Green data
        T   blue;       //!< Blue data
        T   alpha;      //!< Alpha data
        
        constexpr bool    operator==(const RGBA&) const noexcept = default;

        #ifdef YQ_USE_GLM
        constexpr operator glm::vec<4, T, glm::defaultp>() const noexcept
        {
            return { red, green, blue, alpha };
        }
        #endif

        template <typename U>
        requires (std::is_floating_point_v<T> && std::is_integral_v<U>)
        constexpr explicit operator RGBA<U>() const noexcept
        {
            static constexpr const U    mx  = std::numeric_limits<U>::max();
            static constexpr const T    half    = T(0.5);
            return { (U)((red + half) * mx), (U)((green + half) * mx), (U)((blue + half) * mx), (U)((alpha + half) * mx) };
        }
        
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
