////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GBaseData.hpp>

namespace yq {
    struct GGraphData : public GBaseData {
    
        //std::vector<gid_t>      terminals;       // ports in/out (TBD)
    
        virtual bool is_graph() const override { return true; }
        GGraphData(gid_t _id) : GBaseData(_id) {}
        virtual ~GGraphData(){}
    };
}
