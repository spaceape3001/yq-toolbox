////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GBase.hpp>

namespace yq {
    class GNode;

    struct GPortEdgeSearchOptions {
    };

    class GPort : public GBase {
    public:
        
        bool    is_input() const;
        bool    is_output() const;
        
        GNode   node() const;
        
        GPort();
        GPort(const GPort&);
        GPort(GPort&&);
        GPort(GDocumentPtr, gid_t);
        ~GPort();
        GPort& operator=(const GPort&);
        GPort& operator=(GPort&&);
        
        operator bool() const;
        GPortData*  data();
        const GPortData*  data() const;

        void    input(disable_k);
        void    input(enable_k);
        void    output(disable_k);
        void    output(enable_k);

        std::vector<GEdge>      edges(const GPortEdgeSearchOptions& opts={}) const;
        std::vector<GEdge>      inbound(const GPortEdgeSearchOptions& opts={}) const;
        std::vector<GEdge>      outbound(const GPortEdgeSearchOptions& opts={}) const;
    };
}
