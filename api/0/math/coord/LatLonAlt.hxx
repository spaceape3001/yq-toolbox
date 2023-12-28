////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/math/coord/LatLon.hpp>
#include <0/math/coord/LatLonAlt.hpp>

namespace yq {
    template <typename A, typename L>
    constexpr LatLonAlt<A,L>::operator LatLon<A>() const noexcept
    {
        return LatLon<A>(lat, lon);
    }
}
