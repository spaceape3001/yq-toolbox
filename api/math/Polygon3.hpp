////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "PolygonData.hpp"
#include <math/preamble.hpp>
#include <math/Vector3.hpp>

namespace yq {

    YQ_IEEE754_1(Polygon3)
    YQ_ZERO_1(Polygon3, { })

    template <typename T>
    bool is_finite(const Polygon3<T>& poly)
    {
        for(auto& v : poly.vertex)
            if(!is_finite(v))
                return false;
        return true;
    }
    
    template <typename T>
    bool is_nan(const Polygon3<T>& poly)
    {
        for(auto& v : poly.vertex)
            if(is_nan(v))
                return true;
        return false;
    }
}

YQ_TYPE_DECLARE(yq::Polygon3D)
YQ_TYPE_DECLARE(yq::Polygon3F)

