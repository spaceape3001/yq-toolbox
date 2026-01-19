////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/typedef/axbox2.hpp>
#include <yq/typedef/circle2.hpp>
#include <yq/typedef/oval2.hpp>
#include <yq/typedef/polygon2.hpp>
#include <yq/typedef/polyline2.hpp>
#include <yq/typedef/quadrilateral2.hpp>
#include <yq/typedef/segment2.hpp>
#include <yq/typedef/triangle2.hpp>
#include <variant>

namespace yq {

    //! Generic "shape" using a *REASONABLE* list
    template <typename T>
    using Shape2 = std::variant<std::monostate, 
        AxBox2<T>, 
        Circle2<T>, 
        Oval2<T>, 
        Polygon2<T>, 
        Polyline2<T>, 
        Quadrilateral2<T>, 
        Segment2<T>, 
        Triangle2<T>
    >;
    
    using Shape2D   = Shape2<double>;
    using Shape2F   = Shape2<float>;
}
