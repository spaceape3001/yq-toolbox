////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>

namespace yq {

    /*! \brief Simple structure for RGB color
    */
    template <typename T>
    struct RGB {
        using component_type = T;
    
        T   red;    //!< Red data
        T   green;  //!< Green data
        T   blue;   //!< Blue data
        
        constexpr bool    operator==(const RGB&) const noexcept = default;

        constexpr operator glm::vec<3, T, glm::defaultp>() const noexcept
        {
            return { red, green, blue };
        }
        
        template <typename U>
        requires (std::is_floating_point_v<T> && std::is_integral_v<U>)
        constexpr explicit operator RGB<U>() const noexcept
        {
            static constexpr const U    mx  = std::numeric_limits<U>::max();
            static constexpr const T    half    = T(0.5);
            return { (U)((red + half) * mx), (U)((green + half) * mx), (U)((blue + half) * mx) };
        }
        
        template <typename U>
        requires (std::is_integral_v<T> && std::is_floating_point_v<U>)
        constexpr explicit operator RGB<U>() const noexcept
        {
            static constexpr const U    mx  = U(std::numeric_limits<T>::max());
            return { U(red) / mx, U(green) / mx, U(blue) / mx };
        }
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
