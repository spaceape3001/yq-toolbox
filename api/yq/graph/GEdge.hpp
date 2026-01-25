////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GBase.hpp>

namespace yq {
    class GEdge : public GBase {
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
        
        
        GBase               source() const;
        GBase               target() const;
        
        operator bool() const;
    };
}
