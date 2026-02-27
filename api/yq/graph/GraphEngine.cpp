////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphEngine.hxx"
#include <yq/graph/GNodeObject.hpp>
#include <yq/graph/GNodeTemplate.hpp>

namespace yq {

    std::error_code GraphEngine::_initialize(GNodeObject& gno, const GNodeObject::InitAPI& api)
    {
        return gno._initialize(api);
    }

    //const GNodeObjectMeta*    GraphEngine::_meta(GNode gn)
    //{
        
    //}

    //////////////////
    GraphEngine::GraphEngine()
    {
    }
    
    GraphEngine::~GraphEngine()
    {
        _clear();
    }

    void    GraphEngine::_clear()
    {
        for(auto& itr : m_nodes)
            delete itr.second;
        m_nodes.clear();
        m_graph = {};
    }

    void    GraphEngine::clear()
    {
        _clear();
    }

    bool    GraphEngine::empty() const
    {
        return m_nodes.empty();
    }

    GNodeObject*        GraphEngine::node(gid_t i)
    {
        return m_nodes.get(i,nullptr);
    }
    
    const GNodeObject*  GraphEngine::node(gid_t i) const
    {
        return m_nodes.get(i,nullptr);
    }

    const GNodeObjectMeta*  GraphEngine::node_meta() const
    {
        return &meta<GNodeObject>();
    }
}

