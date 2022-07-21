////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "PolygonData.hpp"
#include <math/preamble.hpp>
#include <math/Vector4.hpp>

namespace yq {
    YQ_IEEE754_1(Polygon4)
    YQ_ZERO_1(Polygon4, { })

    template <typename T>
    bool is_finite(const Polygon4<T>& poly)
    {
        for(auto& v : poly.vertex)
            if(!is_finite(v))
                return false;
        return true;
    }
    
    template <typename T>
    bool is_nan(const Polygon4<T>& poly)
    {
        for(auto& v : poly.vertex)
            if(is_nan(v))
                return true;
        return false;
    }
}

YQ_TYPE_DECLARE(yq::Polygon4D)
YQ_TYPE_DECLARE(yq::Polygon4F)

