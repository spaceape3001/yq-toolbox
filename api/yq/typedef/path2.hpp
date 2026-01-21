////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/typedef/vector2.hpp>
#include <variant>

namespace yq {
    template <typename T>
    using path2_step_t = std::variant<std::monostate, 
        Vector2<T>
        // expecting more constraints, bezier, curves, etc
    >; 
    
    template <typename> struct Path2;
    using Path2F    = Path2<float>;
    using Path2D    = Path2<double>;
}
