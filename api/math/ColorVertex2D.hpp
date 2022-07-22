////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

//  This contains some vertex helpers

#include "RGB.hpp"
#include "Vector2.hpp"

namespace yq {
    struct ColorVertexData;
    
    struct ColorVertex2D {
        Vector2D        position;
        RGB3U8          color;
        
        bool operator==(const ColorVertex2D&) const = default;
        operator ColorVertexData() const;
    };
}


