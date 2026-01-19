////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/MetaGraph.hpp>
#include <yq/resource/Resource.hpp>

namespace yq {


    /*! \brief Meta manifest for graphs (ie...traits)
    
        This is a comprehensive listing of things for a graph
    */
    class GraphManifest : public Resource, graph::MetaGraph {
        YQ_RESOURCE_DECLARE(GraphManifest, Resource)
    public:
    
        GManifest();
        ~GManifest();
        
        size_t        data_size() const override;
        
        static void init_meta();
    };
}

