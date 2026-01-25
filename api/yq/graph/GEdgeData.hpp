////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GBaseData.hpp>
#include <yq/graph/GWaypoint.hpp>

namespace yq {
    struct GEdgeData : public GBaseData {
    
        gid_t                   source  = 0;
        gid_t                   target  = 0;
        std::vector<GWaypoint>  waypoints;
    
        virtual bool is_edge() const override { return true; }
        GEdgeData(gid_t _id) : GBaseData(_id) {}
        virtual ~GEdgeData(){}
    };
}
