////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphEngine.hxx"
#include <yq/graph/GNodeObject.hpp>

namespace yq {
    std::error_code GraphEngine::initialize(GNodeObject& gno, const GNodeObject::InitAPI& api)
    {
        return gno._initialize(api);
    }

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

