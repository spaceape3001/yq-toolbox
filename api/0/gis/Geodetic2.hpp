////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/gis/preamble.hpp>
#include <yq-toolbox/meta/InfoBinder.hpp>

namespace yq {
    /*! \brief General purpose geodetic-style structure
    */
    template <typename A>
    struct Geodetic2 {
        A       latitude, longitude;
        
        constexpr bool operator==(const Geodetic2&) const noexcept = default;
    };
}

YQ_TYPE_DECLARE(yq::Geodetic2D)
YQ_TYPE_DECLARE(yq::Geodetic2R)
