////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <yq/unit/declare.hpp>

namespace yq {
    template <typename> struct Vector2;

    using Vector2D                  = Vector2<double>;
    using Vector2F                  = Vector2<float>;
    using Vector2I                  = Vector2<int>;
    using Vector2U                  = Vector2<unsigned>;
    using Vector2M                  = Vector2<unit::Meter>;
    using Vector2CM                 = Vector2<unit::Centimeter>;
    using Vector2MM                 = Vector2<unit::Millimeter>;
    
    struct Vector2S;
}
