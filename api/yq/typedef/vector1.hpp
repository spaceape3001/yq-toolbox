////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <yq/unit/declare.hpp>

namespace yq {
    template <typename> struct Vector1;

    using Vector1D                  = Vector1<double>;
    using Vector1F                  = Vector1<float>;
    using Vector1I                  = Vector1<int>;
    using Vector1U                  = Vector1<unsigned>;
    using Vector1M                  = Vector1<unit::Meter>;
    using Vector1CM                 = Vector1<unit::Centimeter>;
    using Vector1MM                 = Vector1<unit::Millimeter>;
    using Vector1KM                 = Vector1<unit::Kilometer>;
    using Vector1FT                 = Vector1<unit::Foot>;
    using Vector1IN                 = Vector1<unit::Inch>;
    
    struct Vector1S;
}
