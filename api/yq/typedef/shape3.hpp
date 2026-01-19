////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/typedef/axbox3.hpp>
#include <yq/typedef/polygon3.hpp>
#include <yq/typedef/polyline3.hpp>
#include <yq/typedef/segment3.hpp>
#include <yq/typedef/sphere3.hpp>
#include <yq/typedef/tetrahedron3.hpp>
#include <yq/typedef/triangle3.hpp>
#include <variant>

namespace yq {

    //! Generic "shape" using a *REASONABLE* list
    template <typename T>
    using Shape3 = std::variant<std::monostate, 
        AxBox3<T>, 
        Polygon3<T>, 
        Polyline3<T>, 
        Segment3<T>, 
        Sphere3<T>, 
        Tetrahedron3<T>, 
        Triangle3<T>
    >;
    
    using Shape3D   = Shape3<double>;
    using Shape3F   = Shape3<float>;
}
