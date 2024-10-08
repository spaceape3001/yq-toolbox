////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-vulqan/pixel/Painter.hpp>
namespace yq::tachyon {

    using Pixel2 = pixel::Pixel2;
    
    class Painter2 : public Painter {
    public:
    
        Painter2(
        
        );
    };
    
    template <typename C>
    class TypedPainter2 : public Painter2 {
    };

}
