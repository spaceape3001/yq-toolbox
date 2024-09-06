////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_LATLON_HPP 1

#include <yq-toolbox/typedef/latlon.hpp>
#include <yq-toolbox/meta/InfoBinder.hpp>

namespace yq {

    /*! \brief Latitude/Longitude pair
    
    */
    template <typename A>
    struct LatLon {
    
        //! Latitude data
        A   lat;
        
        //! Longitude data
        A   lon;
        
        //! Default constructor
        constexpr LatLon() noexcept = default;
        
        //! Component wise constructor
        constexpr LatLon(A _lat, A _lon) noexcept : lat(_lat), lon(_lon) {}
        
        //! Default equality operator
        constexpr bool operator==(const LatLon&) const noexcept = default;
    };

}

YQ_TYPE_DECLARE(yq::LL)
