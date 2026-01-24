////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GText.hpp>

namespace yq {
    class GNode : public GText {
    public:
        
        GNode();
        GNode(const GNode&);
        GNode(GNode&&);
        GNode(GDocumentPtr, gid_t);
        ~GNode();
        GNode& operator=(const GNode&);
        GNode& operator=(GNode&&);
        
        operator bool() const;
        GNodeData*  data();
        const GNodeData*  data() const;
        
        std::vector<GPort>  ports() const;
        size_t              ports(count_k) const;
        
    };
}
