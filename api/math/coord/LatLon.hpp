////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_LATLON_HPP 1

#include <math/preamble.hpp>

namespace yq {

    /*! \brief Latitude/Longitude pair
    
    */
    template <typename A>
    struct LatLon {
        A   lat;
        A   lon;
        
        constexpr LatLon() noexcept = default;
        constexpr LatLon(A _lat, A _lon) noexcept : lat(_lat), lon(_lon) {}
        
        constexpr bool operator==(const LatLon&) const noexcept = default;
    };

}

