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
        GGraph(GDocumentPtr, gid_t i=0);
        GGraph(GGraph&&);
        ~GGraph();
        GGraph& operator=(const GGraph&);
        GGraph& operator=(GGraph&&);
        
        GGraphData*  data();
        const GGraphData*  data() const;
        
        
        std::vector<GEdge>  edges() const;
        size_t              edges(count_k) const;

        GNode               node(create_k);
        GNode               node(create_k, const GNodeTemplate&);

        std::vector<GNode>  nodes() const;
        size_t              nodes(count_k) const;

        operator bool() const;
    };
}
