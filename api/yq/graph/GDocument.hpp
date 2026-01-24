////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/resource/Resource.hpp>
#include <yq/graph/graph_types.hpp>

namespace yq {
    /*! \brief Graph Document
    
        The graph document serves two purposes
        1) Graph Relationship
        2) Rendering Data (For GUI editors)
        
        IDs... may be compacted on save?  Or, more likely, not
    */
    class GDocument : public Resource {
        YQ_RESOURCE_DECLARE(GDocument, Resource)
    public:
    
        GDocument();
        GDocument(new_k);
        ~GDocument();
        
        static void init_meta();
        
        GBaseData*          data(gid_t);
        const GBaseData*    data(gid_t) const;
        
        GEdgeData*          edge(create_k);
        GEdgeData*          edge(create_k, gid_t);
        GEdgeData*          edge(gid_t);
        const GEdgeData*    edge(gid_t) const;

        GGraphData*         graph(create_k);
        GGraphData*         graph(create_k, gid_t);
        GGraphData*         graph(gid_t);
        const GGraphData*   graph(gid_t) const;

        GNodeData*          node(create_k);
        GNodeData*          node(create_k, gid_t);
        GNodeData*          node(gid_t);
        const GNodeData*    node(gid_t) const;

        GLineData*          line(create_k);
        GLineData*          line(create_k, gid_t);
        GLineData*          line(gid_t);
        const GLineData*    line(gid_t) const;

        GPortData*          port(create_k);
        GPortData*          port(create_k, gid_t);
        GPortData*          port(gid_t);
        const GPortData*    port(gid_t) const;

        GShapeData*         shape(create_k);
        GShapeData*         shape(create_k, gid_t);
        GShapeData*         shape(gid_t);
        const GShapeData*   shape(gid_t) const;

        GTextData*          text(create_k);
        GTextData*          text(create_k, gid_t);
        GTextData*          text(gid_t);
        const GTextData*    text(gid_t) const;
        
        //GViewData*          _view(create_k);
        //GViewData*          _view(gid_t);
        //const GViewData*    _view(gid_t) const;
        
        
        void                reserve(gid_t);
        
        size_t data_size() const override { return 0; }
        
    private:
        using GBaseDataVector = std::vector<GBaseData*>;
    
        std::vector<GBaseData*>     m_data;

        template <typename T> T*    _create();
        template <typename T> T*    _create(gid_t);
        
        void                _expand(gid_t);
    };

}

