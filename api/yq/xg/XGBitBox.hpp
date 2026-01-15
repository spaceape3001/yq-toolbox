////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/color/RGBA.hpp>
#include <yq/shape/Size2.hpp>
#include <yq/vector/Vector2.hpp>

#ifdef NAN
    #undef NAN
#endif

namespace yq {
    struct XGBitBox {
        //! Background color to the object
        RGBA4F                  bgcolor     = { 0., 0., 0., 0. };
        
        //! (Center) Position for shapes (ie, box, text, nodes)
        Vector2F                position    = NAN;

        //! Size for shapes (box, text, nodes)
        Size2F                  size        = NAN;
        
    };
}
