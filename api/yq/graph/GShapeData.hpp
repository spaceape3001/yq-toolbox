////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GBaseData.hpp>
#include <yq/shape/Size2.hpp>
#include <yq/vector/Vector2.hpp>

#ifdef NAN
#undef NAN
#endif

namespace yq {
    struct GShapeData : public GBaseData, public GPosSizeData {
        
        symbol::TransformMode   transform;

        GShapeData(gid_t);
        GShapeData(const GShapeData&);
        virtual ~GShapeData();
        GBaseData*  clone() const;
        virtual bool is_shape() const override { return true; }
        
    };
}
