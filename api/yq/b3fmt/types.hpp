////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/b3fmt/typedef.hpp>
#include <yq/units.hpp>
#include <yq/color/RGBA.hpp>
#include <yq/container/Vector.hpp>
#include <yq/coord/Coord1.hpp>
#include <yq/coord/Coord2.hpp>
#include <yq/coord/Coord3.hpp>
#include <yq/coord/Coord4.hpp>
#include <yq/coord/Coord5.hpp>
#include <yq/coord/Coord6.hpp>
#include <yq/shape/Size1.hpp>
#include <yq/shape/Size2.hpp>
#include <yq/shape/Size3.hpp>
#include <yq/shape/Size4.hpp>
#include <yq/tensor/Tensor23.hpp>
#include <yq/vector/Vector1.hpp>
#include <yq/vector/Vector2.hpp>
#include <yq/vector/Vector3.hpp>
#include <yq/vector/Vector4.hpp>
#include <vector>

#ifdef NAN
    #undef NAN
#endif

namespace yq::b3 {

    struct Color {
        std::string def;
        
        auto operator<=>(const Color&) const = default;
        
        operator RGBA4F() const;
    };

    struct Brush {
        Color       color;
        
        bool operator==(const Brush&) const = default;
    };

    struct CoordN {
        Vector<int>  indices;
        
        operator Coord1I() const;
        operator Coord2I() const;
        operator Coord3I() const;
        operator Coord4I() const;
        operator Coord5I() const;
        operator Coord6I() const;
    };

    struct CountN {
        Vector<int> axes;
        
        operator Size1I() const;
        operator Size2I() const;
        operator Size3I() const;
        operator Size4I() const;
    };
    
    struct Font {
        std::string family;
        double      size    = 0.;
        
        bool operator==(const Font&) const = default;
    };

    struct Pen {
        Color       color;
        double      width   = 0.;
        PenStyle    style   = PenStyle::Solid;
        
        bool operator==(const Pen&) const = default;
    };

    struct PointN {
        Vector<double> axes;
        
        operator Vector1D() const;
        operator Vector2D() const;
        operator Vector3D() const;
        operator Vector4D() const;
    };
    
    struct SizeN {
        Vector<double> axes;
        
        operator Size1D() const;
        operator Size2D() const;
        operator Size3D() const;
        operator Size4D() const;
    };
    
    struct Transform {
        Tensor23D       matrix      = NAN;
        Vector2D        origin      = NAN;
        unit::Degree    rotate      = NAN;
        Vector2D        scale       = NAN;
        Vector2D        skew        = NAN;
        Vector2D        translate   = NAN;
    };
    
    struct VectorN {
        Vector<double> axes;
        
        operator Vector1D() const;
        operator Vector2D() const;
        operator Vector3D() const;
        operator Vector4D() const;
    };
}
