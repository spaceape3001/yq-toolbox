////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/container/forward.hpp>
#include <yq/typedef/vector1.hpp>
#include <yq/typedef/vector2.hpp>
#include <yq/typedef/vector3.hpp>
#include <yq/typedef/vector4.hpp>
#include <string>

namespace yq {
    template <typename> struct AxCorners2;
    template <typename> struct AxCorners3;
    template <typename> class Ref;
    struct IgCase;
}

namespace yq::b3 {
    enum class PenStyle {
        Solid,
        Dash,
        Dot,
        DashDot
    };

    struct CoordN;
    struct CountN;
    struct Brush;
    struct Pen;
    struct Font;
    struct PointN;
    struct SizeN;
    struct VectorN;

    using IntegerSet    = Set<int>;

    using AxCorners23D          = AxCorners2<Vector3D>;
    using AxCorners33D          = AxCorners3<Vector3D>;

    using DoubleMap         = Map<std::string,double,IgCase>;
}
