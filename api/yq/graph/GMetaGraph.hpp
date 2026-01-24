////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/resource/ResourceLibrary.hpp>
#include <yq/typedef/g_meta_graph.hpp>
#include <yq/typedef/g_node_template.hpp>

namespace yq {


    /*! \brief Meta Graph
    
        This is a comprehensive listing of things for a graph ecosystem; nodes, edges, ports, rules, etc
    */
    class GMetaGraph : public ResourceLibrary {
        YQ_RESOURCE_DECLARE(GMetaGraph, ResourceLibrary)
    public:
    
        GMetaGraph();
        ~GMetaGraph();
        
        size_t        data_size() const override;
        const auto& nodes() const { return m_nodes; }
        
        static void init_meta();
        
        
    protected:
        virtual void    post_add(ResourcePtr) override;
    
    private:
        std::vector<GNodeTemplateCPtr>  m_nodes;
    };
}

