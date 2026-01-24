////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GBaseData.hpp>
#include <yq/vector/Vector2.hpp>
#include <variant>

#ifdef NAN
    #undef NAN
#endif

namespace yq {

    using gposition_t   = std::variant<std::monostate, 
        gid_t,      // Node/Port/Text/etc
        float,      // Fraction along the span between a & b
        Vector2D    // x/y
    >;

    struct GWaypoint {
        gposition_t     position;
        Vector2D        direction = NAN;
    };


    struct GLineData : public GBaseData {
    
        std::vector<GWaypoint>      waypoints;
        
        virtual bool is_line() const override { return true; }
        GLineData(gid_t _id) : GBaseData(_id) {}
        virtual ~GLineData(){}
        
    };
}
