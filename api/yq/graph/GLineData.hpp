////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GBaseData.hpp>
#include <yq/graph/GWaypoint.hpp>

#ifdef NAN
    #undef NAN
#endif

namespace yq {

    struct GLineData : public GBaseData {
    
        std::vector<GWaypoint>      waypoints;
        
        virtual bool is_line() const override { return true; }
        GLineData(gid_t _id);
        GLineData(const GLineData&);
        virtual ~GLineData();
        GBaseData*  clone() const;
        
    };
}
