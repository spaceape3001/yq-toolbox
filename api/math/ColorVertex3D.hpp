////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

//  This contains some vertex helpers

#include "RGB.hpp"
#include "Vector3.hpp"

namespace yq {
    struct ColorVertexData;
    
    struct ColorVertex3D {
        Vector3D        position;
        RGB3U8          color;
        
        bool operator==(const ColorVertex3D&) const = default;
        operator ColorVertexData() const;
    };
}


