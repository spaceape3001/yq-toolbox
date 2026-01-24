////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GBaseData.hpp>

namespace yq {
    struct GNodeData : public GBaseData {
        virtual bool is_node() const override { return true; }
        GNodeData(gid_t _id) : GBaseData(_id) {}
        virtual ~GNodeData(){}
    };
}
