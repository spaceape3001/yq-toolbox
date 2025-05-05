////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/unit/declare.hpp>

namespace yq {
    template <typename> struct Range;

    using RangeD    = Range<double>;
    using RangeF    = Range<float>;
    using RangeI    = Range<int>;
    using RangeU    = Range<unsigned>;
    using RangeM    = Range<unit::Meter>;
    using RangeCM   = Range<unit::Centimeter>;
    using RangeMM   = Range<unit::Millimeter>;
}
