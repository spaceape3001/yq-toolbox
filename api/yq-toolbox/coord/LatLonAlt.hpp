////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_LATLONALT_HPP 1

#include <yq-toolbox/typedef/latlonalt.hpp>
#include <yq-toolbox/meta/InfoBinder.hpp>

namespace yq {
    template <typename A> struct LatLon;

    /*! \brief Latitude, Longitude, Altitude tuple
    
        \tparam A   Angle type
        \tparam L   Length type
    */
    template <typename A, typename L>
    struct LatLonAlt {
        //! Latitude value
        A   lat;
        
        //! Longitude value
        A   lon;
        
        //! Altitude value
        L   alt;
        
        //! Default constructor
        constexpr LatLonAlt() noexcept = default;
        
        //! Component wise constructor
        constexpr LatLonAlt(A _lat, A _lon, L _alt) noexcept : lat(_lat), lon(_lon), alt(_alt) {}
        
        //! Constructs from LatLon
        explicit constexpr LatLonAlt(const LatLon<A>&) noexcept;

        //! Constructs from LatLon and altitude
        constexpr LatLonAlt(const LatLon<A>&, L) noexcept;
        
        //! Implicit conversion to lat-lon
        constexpr operator LatLon<A>() const noexcept;
        
        //! Implicit conversion to other lat-lon-alt type
        template <typename A2, typename L2>
        requires (std::is_convertible_v<A,A2> && std::is_convertible_v<L,L2>)
        constexpr operator LatLonAlt<A2,L2>() const noexcept
        {
            return LatLonAlt<A2,L2>(A2(lat), A2(lon), L2(alt));
        }
        
        //! Defaulted equality operator
        constexpr bool operator==(const LatLonAlt&) const noexcept = default;
    };

}

YQ_TYPE_DECLARE(yq::LLH)
YQ_TYPE_DECLARE(yq::LLM)

