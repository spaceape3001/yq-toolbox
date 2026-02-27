////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GGraph.hpp>
#include <yq/graph/GNode.hpp>
#include <yq/graph/GNodeObject.hpp>

namespace yq {

    class GNodeObject;
    class GNodeObjectMeta;

    //! Utility base for anything processing graphs for actions
    class GraphEngine {
    public:
    
        virtual void        clear();
    
        bool                empty() const;
    
        GNodeObject*        node(gid_t);
        const GNodeObject*  node(gid_t) const;
    
    protected:
        GGraph                      m_graph;
        Map<gid_t, GNodeObject*>    m_nodes;
        
        GraphEngine();
        ~GraphEngine();
        
        virtual const GNodeObjectMeta*  node_meta() const;
        
        static std::error_code _initialize(GNodeObject&, const GNodeObject::InitAPI&);
        
        // creates but does *NOT* initialize nor add to the map
        //static const GNodeObjectMeta*    _meta(GNode);
        
        
    private:
        void    _clear();
    };
}
