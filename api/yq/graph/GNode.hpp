////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GBase.hpp>
#include <yq/typedef/size2.hpp>
#include <yq/typedef/vector2.hpp>
#include <yq/symbol/transform.hpp>

namespace yq {
    namespace symbol {
        class PinBase;
    }
    
    struct GNodeEdgeSearchOptions {
        bool    ports   = false;
    };

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
        GNodeData*              data();
        const GNodeData*        data() const;
        
        std::vector<GEdge>      edges(const GNodeEdgeSearchOptions& opts={}) const;
        
        std::vector<GEdge>      inbound(const GNodeEdgeSearchOptions& opts={}) const;
        std::vector<GEdge>      outbound(const GNodeEdgeSearchOptions& opts={}) const;
        
        GPort                   port(create_k, const std::string& key={});
        GPort                   port(create_k, const symbol::PinBase&, const std::string& key={});
        
        //! First port with key
        GPort                   port(const std::string& key) const;
        GPort                   port(in_k, const std::string& key) const;
        GPort                   port(out_k, const std::string& key) const;
        
        std::vector<GPort>      ports() const;
        size_t                  ports(count_k) const;
        
        Vector2D                position() const;
        void                    position(set_k, const Vector2D&);
        Size2D                  size() const;
        void                    size(set_k, const Size2D&);
        
        symbol::TransformMode   transform() const;
        void                    transform(set_k, symbol::TransformMode);
        
        std::string_view        type() const;
        
    private:
        GPortData*              _port(create_k, const std::string& key);
    };
}
