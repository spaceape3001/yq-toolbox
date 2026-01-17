////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "transform.hpp"
#include <yq/vector/Vector2.hpp>

namespace yq::symbol::transform {
    namespace {
        // VERIFY!
        static inline Vector2F op_090 (Vector2F v) 
        {
            return Vector2F(v.y, -v.x);
        }

        static inline Vector2F op_180 (Vector2F v) 
        {
            return Vector2F(-v.x, -v.y);
        }

        static inline Vector2F op_270 (Vector2F v) 
        {
            return Vector2F(-v.y, v.x);
        }
        
        static inline Vector2F op_swap(Vector2F v)
        {
            return Vector2F(v.y, v.x);
        }
        
        static inline Vector2F op_horz(Vector2F v)
        {
            return Vector2F(-v.x, v.y);
        }
    
        static inline Vector2F op_vert(Vector2F v)
        {
            return Vector2F(v.x, -v.y);
        }
    }

    Vector2F        identity(Vector2F v)
    {
        return v;
    }
    
    Vector2F        rot90(Vector2F v)
    {
        return op_090(v);
    }
    
    Vector2F        rot180(Vector2F v)
    {
        return op_180(v);
    }
    
    Vector2F        rot270(Vector2F v)
    {
        return op_270(v);
    }
    
    Vector2F        hflip(Vector2F v)
    {
        return op_horz(v);
    }
    
    Vector2F        hflip90(Vector2F v)
    {
        return op_090(op_horz(v));
    }
    
    Vector2F        hflip180(Vector2F v)
    {
        return op_180(op_horz(v));
    }
    
    Vector2F        hflip270(Vector2F v)
    {
        return op_270(op_horz(v));
    }
    
    Vector2F        vflip(Vector2F v)
    {
        return op_090(op_vert(v));
    }
    
    Vector2F        vflip90(Vector2F v)
    {
        return op_090(op_vert(v));
    }
    
    Vector2F        vflip180(Vector2F v)
    {
        return op_180(op_vert(v));
    }
    
    Vector2F        vflip270(Vector2F v)
    {
        return op_270(op_vert(v));
    }
    
    Vector2F        swap(Vector2F v)
    {
        return op_swap(v);
    }
    
    Vector2F        swap90(Vector2F v)
    {
        return op_090(op_swap(v));
    }
    
    Vector2F        swap180(Vector2F v)
    {
        return op_180(op_swap(v));
    }
    
    Vector2F        swap270(Vector2F v)
    {
        return op_270(op_swap(v));
    }
}

namespace yq::symbol {
    FNTransform     function(TransformMode tm)
    {
        switch(tm){
        case TransformMode::ROT_090:
            return transform::rot90;
        case TransformMode::ROT_180:
            return transform::rot180;
        case TransformMode::ROT_270:
            return transform::rot270;
        case TransformMode::HORZ:
            return transform::hflip;
        case TransformMode::HORZ_090:
            return transform::hflip90;
        case TransformMode::HORZ_180:
            return transform::hflip180;
        case TransformMode::HORZ_270:
            return transform::hflip270;
        case TransformMode::VERT:
            return transform::vflip;
        case TransformMode::VERT_090:
            return transform::vflip90;
        case TransformMode::VERT_180:
            return transform::vflip180;
        case TransformMode::VERT_270:
            return transform::vflip270;
        case TransformMode::SWAP:
            return transform::swap;
        case TransformMode::SWAP_090:
            return transform::swap90;
        case TransformMode::SWAP_180:
            return transform::swap180;
        case TransformMode::SWAP_270:
            return transform::swap270;
        case TransformMode::IDENTITY:
        default:
            return transform::identity;
        }
    }
    
    /*
        switch(tm){
        case TransformMode::IDENTITY:
        case TransformMode::ROT_090:
        case TransformMode::ROT_180:
        case TransformMode::ROT_270:
        case TransformMode::HORZ:
        case TransformMode::HORZ_090:
        case TransformMode::HORZ_180:
        case TransformMode::HORZ_270:
        case TransformMode::VERT:
        case TransformMode::VERT_090:
        case TransformMode::VERT_180:
        case TransformMode::VERT_270:
        case TransformMode::SWAP:
        case TransformMode::SWAP_090:
        case TransformMode::SWAP_180:
        case TransformMode::SWAP_270:
        default:
        }
    */

    TransformMode    rotate_90(TransformMode tm)
    {
        switch(tm){
        case TransformMode::IDENTITY:
            return TransformMode::ROT_090;
        case TransformMode::ROT_090:
            return TransformMode::ROT_180;
        case TransformMode::ROT_180:
            return TransformMode::ROT_270;
        case TransformMode::ROT_270:
            return TransformMode::IDENTITY;
        case TransformMode::HORZ:
            return TransformMode::HORZ_090;
        case TransformMode::HORZ_090:
            return TransformMode::HORZ_180;
        case TransformMode::HORZ_180:
            return TransformMode::HORZ_270;
        case TransformMode::HORZ_270:
            return TransformMode::HORZ;
        case TransformMode::VERT:
            return TransformMode::VERT_090;
        case TransformMode::VERT_090:
            return TransformMode::VERT_180;
        case TransformMode::VERT_180:
            return TransformMode::VERT_180;
        case TransformMode::VERT_270:
            return TransformMode::VERT_270;
        case TransformMode::SWAP:
            return TransformMode::SWAP_090;
        case TransformMode::SWAP_090:
            return TransformMode::SWAP_180;
        case TransformMode::SWAP_180:
            return TransformMode::SWAP_270;
        case TransformMode::SWAP_270:
            return TransformMode::SWAP;
        default:
            return tm;
        }
    }
    
    TransformMode    rotate_180(TransformMode tm)
    {
        switch(tm){
        case TransformMode::IDENTITY:
            return TransformMode::ROT_180;
        case TransformMode::ROT_090:
            return TransformMode::ROT_270;
        case TransformMode::ROT_180:
            return TransformMode::IDENTITY;
        case TransformMode::ROT_270:
            return TransformMode::ROT_090;
        case TransformMode::HORZ:
            return TransformMode::HORZ_180;
        case TransformMode::HORZ_090:
            return TransformMode::HORZ_270;
        case TransformMode::HORZ_180:
            return TransformMode::HORZ;
        case TransformMode::HORZ_270:
            return TransformMode::HORZ_090;
        case TransformMode::VERT:
            return TransformMode::VERT_180;
        case TransformMode::VERT_090:
            return TransformMode::VERT_270;
        case TransformMode::VERT_180:
            return TransformMode::VERT;
        case TransformMode::VERT_270:
            return TransformMode::VERT_090;
        case TransformMode::SWAP:
            return TransformMode::SWAP_180;
        case TransformMode::SWAP_090:
            return TransformMode::SWAP_270;
        case TransformMode::SWAP_180:
            return TransformMode::SWAP;
        case TransformMode::SWAP_270:
            return TransformMode::SWAP_090;
        default:
            return tm;
        }
    }
    
    TransformMode    rotate_270(TransformMode tm)
    {
        switch(tm){
        case TransformMode::IDENTITY:
            return TransformMode::ROT_270;
        case TransformMode::ROT_090:
            return TransformMode::IDENTITY;
        case TransformMode::ROT_180:
            return TransformMode::ROT_090;
        case TransformMode::ROT_270:
            return TransformMode::ROT_180;
        case TransformMode::HORZ:
            return TransformMode::HORZ_270;
        case TransformMode::HORZ_090:
            return TransformMode::HORZ;
        case TransformMode::HORZ_180:
            return TransformMode::HORZ_090;
        case TransformMode::HORZ_270:
            return TransformMode::HORZ_180;
        case TransformMode::VERT:
            return TransformMode::VERT_270;
        case TransformMode::VERT_090:
            return TransformMode::VERT;
        case TransformMode::VERT_180:
            return TransformMode::VERT_090;
        case TransformMode::VERT_270:
            return TransformMode::VERT_180;
        case TransformMode::SWAP:
            return TransformMode::SWAP_270;
        case TransformMode::SWAP_090:
            return TransformMode::SWAP;
        case TransformMode::SWAP_180:
            return TransformMode::SWAP_090;
        case TransformMode::SWAP_270:
            return TransformMode::SWAP_180;
        default:
            return tm;
        }
    }

    TransformTypes   types(TransformMode tm)
    {
        switch(tm){
        case TransformMode::IDENTITY:
            return {};
        case TransformMode::ROT_090:
        case TransformMode::ROT_180:
        case TransformMode::ROT_270:
            return TransformType::Rotation;
        case TransformMode::HORZ:
            return TransformType::HorizontalFlip;
        case TransformMode::HORZ_090:
        case TransformMode::HORZ_180:
        case TransformMode::HORZ_270:
            return { TransformType::HorizontalFlip, TransformType::Rotation };
        case TransformMode::VERT:
            return TransformType::VerticalFlip;
        case TransformMode::VERT_090:
        case TransformMode::VERT_180:
        case TransformMode::VERT_270:
            return { TransformType::VerticalFlip, TransformType::Rotation };
        case TransformMode::SWAP:   
            return TransformType::XYSwitch;
        case TransformMode::SWAP_090:
        case TransformMode::SWAP_180:
        case TransformMode::SWAP_270:
            return { TransformType::XYSwitch, TransformType::Rotation };
        default:
            return {};
        }
    }
}
