////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GLineData.hpp>

namespace yq {
    struct GEdgeData : public GLineData {
    
        // start/end will be in the waypoints (front/back)
    
        virtual bool is_edge() const override { return true; }
        GEdgeData(gid_t _id) : GLineData(_id) {}
        virtual ~GEdgeData(){}
    };
}
