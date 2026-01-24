////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>
#include <yq/graph/GBase.hpp>

namespace yq {

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

        operator bool() const;
    };
}
