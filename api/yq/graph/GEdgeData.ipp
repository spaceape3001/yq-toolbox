////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GEdgeData.hpp"

namespace yq {
    gid_t GEdgeData::source() const
    {
        if(waypoints.empty())
            return 0;
        if(auto p = std::get_if<gid_t>(&waypoints.front().position)){
            return *p;
        } else
            return 0;
    }
    
    gid_t GEdgeData::target() const
    {
        if(waypoints.size() < 2)
            return 0;
        if(auto p = std::get_if<gid_t>(&waypoints.back().position)){
            return *p;
        } else
            return 0;
    }
}


