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
        
        
        GBase   source() const;
        GNode   source(node_k) const;
        GPort   source(port_k) const;
        
        GBase   target() const;
        GNode   target(node_k) const;
        GPort   target(port_k) const;
        
        
        operator bool() const;
    };
}
