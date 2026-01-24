////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GLine.hpp>

namespace yq {
    class GEdge : public GLine {
    public:
    
        GEdge();
        GEdge(const GEdge&);
        GEdge(GEdge&&);
        GEdge(GDocumentPtr, gid_t);
        ~GEdge();
        
        GEdge& operator=(const GEdge&);
        GEdge& operator=(GEdge&&);
        
        GEdgeData*          data();
        const GEdgeData*    data() const;
        
        operator bool() const;
    };
}
