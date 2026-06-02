////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <yq/unit/declare.hpp>

namespace yq {
    template <typename> struct Vector4;

    using Vector4D                  = Vector4<double>;
    using Vector4F                  = Vector4<float>;
    using Vector4I                  = Vector4<int>;
    using Vector4U                  = Vector4<unsigned>;
    using Vector4M                  = Vector4<unit::Meter>;
    using Vector4CM                 = Vector4<unit::Centimeter>;
    using Vector4MM                 = Vector4<unit::Millimeter>;
    using Vector4KM                 = Vector4<unit::Kilometer>;
    using Vector4FT                 = Vector4<unit::Foot>;
    using Vector4IN                 = Vector4<unit::Inch>;
    
    struct Vector4S;
}
