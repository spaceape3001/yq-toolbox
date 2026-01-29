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
    
        GGraphData(gid_t _id);
        GGraphData(const GGraphData&);
        virtual ~GGraphData();
        virtual GBaseData*  clone() const override;
        virtual bool is_graph() const override { return true; }
    };
}
