////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/coord/LatLon.hpp>
#include <math/coord/LatLonAlt.hpp>

namespace yq {
    template <typename A, typename L>
    constexpr LatLonAlt<A,L>::operator LatLon<A>() const noexcept
    {
        return LatLon<A>(lat, lon);
    }
}
