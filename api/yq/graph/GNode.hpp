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
    namespace symbol {
        class PinBase;
    }

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
        
        GPort               port(create_k, const symbol::PinBase&, const std::string& key={});
        
        std::vector<GPort>  ports() const;
        size_t              ports(count_k) const;
        
        
        Vector2D            position() const;
        void                position(set_k, const Vector2D&);
        
        std::string_view    type() const;
    };
}
