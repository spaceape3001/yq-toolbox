////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/pixel/Painter.hpp>

namespace yq::pixel {

    class Painter2 : public Painter {
    public:
    
        Painter2(
        
        );
    };
    
    template <typename C>
    class TypedPainter2 : public Painter2 {
    };

}
