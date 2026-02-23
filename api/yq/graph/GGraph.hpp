////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>
#include <yq/graph/GBase.hpp>

namespace yq {

    class GNodeTemplate;

    /*! \brief Graph in the document
    
        Graph data in the document.  If the id is NOT zero, 
        then it's a subgraph.
    */
    class GGraph : public GBase {
    public:
        
        GGraph();
        GGraph(create_k);
        GGraph(const GGraph&);
        
        // TODO ... weave in the readonly
        GGraph(load_k, std::string_view);
        GGraph(read_only_k, GDocumentCPtr);
        
        GGraph(GDocumentPtr, gid_t i=0);
        GGraph(GGraph&&);
        ~GGraph();
        GGraph& operator=(const GGraph&);
        GGraph& operator=(GGraph&&);
        
        GGraphData*  data();
        const GGraphData*  data() const;
        
        GEdge               connect(const GNode&, const GNode&);
        GEdge               connect(const GNode&, const GPort&);
        GEdge               connect(const GPort&, const GNode&);
        GEdge               connect(const GPort&, const GPort&);
        
        bool                connected(const GNode&, const GNode&) const;
        bool                connected(const GNode&, const GPort&) const;
        bool                connected(const GPort&, const GNode&) const;
        bool                connected(const GPort&, const GPort&) const;
        
        GEdge               connection(const GNode&, const GNode&) const;
        GEdge               connection(const GNode&, const GPort&) const;
        GEdge               connection(const GPort&, const GNode&) const;
        GEdge               connection(const GPort&, const GPort&) const;
        
        std::vector<GEdge>  edges() const;
        size_t              edges(count_k) const;

        GNode               node(create_k);
        GNode               node(create_k, const GNodeTemplate&);

        std::vector<GNode>  nodes() const;
        size_t              nodes(count_k) const;

        operator bool() const;
    };
}
