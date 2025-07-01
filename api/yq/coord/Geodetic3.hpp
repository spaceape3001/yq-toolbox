////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/typedef/geodetic3.hpp>
#include <yq/meta/MetaBinder.hpp>

namespace yq {
    /*! \brief General purpose geodetic-style structure
    */
    template <typename A, typename L>
    struct Geodetic3 {
        A       latitude, longitude;
        L       altitude;

        constexpr bool operator==(const Geodetic3&) const noexcept = default;
    };
}

YQ_TYPE_DECLARE(yq::Geodetic3DF)
YQ_TYPE_DECLARE(yq::Geodetic3DM)
YQ_TYPE_DECLARE(yq::Geodetic3RF)
YQ_TYPE_DECLARE(yq::Geodetic3RM)
