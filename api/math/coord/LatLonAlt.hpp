////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_LATLONALT_HPP 1

#include <math/preamble.hpp>

namespace yq {
    /*! \brief Latitude, Longitude, Altitude tuple
    */
    template <typename A, typename L>
    struct LatLonAlt {
        A   lat;
        A   lon;
        L   alt;
        
        constexpr LatLonAlt() noexcept = default;
        constexpr LatLonAlt(A _lat, A _lon, L _alt) noexcept : lat(_lat), lon(_lon), alt(_alt) {}
        
        explicit constexpr LatLonAlt(const LatLon<A>&) noexcept;
        explicit constexpr LatLonAlt(const LatLon<A>&, L) noexcept;
        
        constexpr operator LatLon<A>() const noexcept;
        
        template <typename A2, typename L2>
        requires (std::is_convertible_v<A,A2> && std::is_convertible_v<L,L2>)
        constexpr operator LatLonAlt<A2,L2>() const noexcept
        {
            return LatLonAlt<A2,L2>(A2(lat), A2(lon), L2(alt));
        }
        
        constexpr bool operator==(const LatLonAlt&) const noexcept = default;
    };

}

