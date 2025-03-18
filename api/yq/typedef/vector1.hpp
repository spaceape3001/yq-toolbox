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
    using Vector1M                  = Vector1<Meter>;
    
    struct Vector1S;
}
