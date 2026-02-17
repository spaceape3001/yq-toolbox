////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>
#include <yq/core/Enum.hpp>
#include <yq/core/Flag.hpp>
#include <yq/core/Flags.hpp>
#include <yq/meta/MetaBinder.hpp>
#include <yq/typedef/vector2.hpp>

namespace yq::symbol {
    YQ_ENUM(TransformMode, ,
        IDENTITY = 0,
        ROT_090,
        ROT_180,
        ROT_270,
        
        HORZ,
        HORZ_090,
        HORZ_180,
        HORZ_270,
        
        VERT,
        VERT_090,
        VERT_180,
        VERT_270,
        
        SWAP,
        SWAP_090,
        SWAP_180,
        SWAP_270
    );

    typedef Vector2F (*FNTransform)(Vector2F);
    
    enum class TransformType {
        HorizontalFlip,
        VerticalFlip,
        XYSwitch,
        Rotation
    };
    
    using TransformTypes    = Flags<TransformType>;

    namespace transform {
        Vector2F        identity(Vector2F);
        Vector2F        rot90(Vector2F);
        Vector2F        rot180(Vector2F);
        Vector2F        rot270(Vector2F);
        Vector2F        hflip(Vector2F);
        Vector2F        hflip90(Vector2F);
        Vector2F        hflip180(Vector2F);
        Vector2F        hflip270(Vector2F);
        Vector2F        vflip(Vector2F);
        Vector2F        vflip90(Vector2F);
        Vector2F        vflip180(Vector2F);
        Vector2F        vflip270(Vector2F);
        Vector2F        swap(Vector2F);
        Vector2F        swap90(Vector2F);
        Vector2F        swap180(Vector2F);
        Vector2F        swap270(Vector2F);
    }

    FNTransform         function(TransformMode);
    TransformMode       rotate_90(TransformMode);
    TransformMode       rotate_180(TransformMode);
    TransformMode       rotate_270(TransformMode);
    TransformTypes      types(TransformMode);

/*    
    TransformMode       horzflip(TransformMode);
    TransformMode       vertflip(TransformMode);
    TransformMode       swapxy(TransformMode);
*/
}

YQ_TYPE_DECLARE(yq::symbol::TransformMode)
