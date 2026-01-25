////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GBase.hpp>
#include <yq/typedef/size2.hpp>
#include <yq/typedef/vector2.hpp>

namespace yq {
    class GNode : public GBase {
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
        
        std::string_view    node_template() const;
        
        Vector2F            position() const;
        void                position(set_k, const Vector2F&);
        
    };
}
