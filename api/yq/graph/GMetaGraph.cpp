////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GMetaGraph.hpp"
#include "GNodeTemplate.hpp"
#include <yq/resource/ResourceLibraryMetaWriter.hpp>

YQ_RESOURCE_IMPLEMENT(yq::GMetaGraph)

namespace yq {
    GMetaGraph::GMetaGraph()
    {
    }
    
    GMetaGraph::~GMetaGraph()
    {
    }
        
    size_t        GMetaGraph::data_size() const 
    {
        return 0;
    }

    void    GMetaGraph::post_add(ResourcePtr rp) 
    {
        if(const GNodeTemplate* nt = dynamic_cast<const GNodeTemplate*>(rp.ptr()))
            m_nodes.push_back(nt);
    }
        
    void GMetaGraph::init_meta()
    {
        auto w = writer<GMetaGraph>();
        w.description("Library of Creatable Nodes");
        w.resource<GNodeTemplate>();
    }
}

