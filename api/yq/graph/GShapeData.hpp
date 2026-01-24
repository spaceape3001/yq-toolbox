////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GBaseData.hpp>

namespace yq {
    struct GShapeData : public GBaseData {
        
        virtual bool is_shape() const override { return true; }
        GShapeData(gid_t _id) : GBaseData(_id) {}
        virtual ~GShapeData(){}
        
    };
}
