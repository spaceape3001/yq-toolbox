////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/raster/Painter.hpp>

namespace yq::raster {

    class Painter2 : public Painter {
    public:
    
        Painter2(
        
        );
    };
    
    template <typename C>
    class TypedPainter2 : public Painter2 {
    };

}
