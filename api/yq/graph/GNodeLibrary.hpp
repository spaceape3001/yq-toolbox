////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/resource/ResourceLibrary.hpp>
#include <yq/typedef/g_node_template.hpp>

namespace yq::graph {


    /*! \brief Library of nodes
    
        This is a comprehensive listing of things for a graph
    */
    class GNodeLibrary : public ResourceLibrary {
        YQ_RESOURCE_DECLARE(GNodeLibrary, ResourceLibrary)
    public:
    
        GNodeLibrary();
        ~GNodeLibrary();
        
        size_t        data_size() const override;
        
        static void init_meta();
    };
}

