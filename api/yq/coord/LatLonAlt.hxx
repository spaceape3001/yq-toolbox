////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/coord/LatLon.hpp>
#include <yq/coord/LatLonAlt.hpp>

namespace yq {
    template <typename A, typename L>
    constexpr LatLonAlt<A,L>::operator LatLon<A>() const noexcept
    {
        return LatLon<A>(lat, lon);
    }
}
