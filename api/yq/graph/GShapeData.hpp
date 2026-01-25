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
    struct GShapeData : public GBaseData {
        
        Vector2F            position    = NAN;
        Size2F              size        = NAN;

        virtual bool is_shape() const override { return true; }
        GShapeData(gid_t _id) : GBaseData(_id) {}
        virtual ~GShapeData(){}
        
    };
}
