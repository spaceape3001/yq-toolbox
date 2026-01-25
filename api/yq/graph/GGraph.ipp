////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GGraph.hpp"
#include "GGraphData.hpp"
#include "GNodeTemplate.hpp"
#include "GDocument.hxx"

namespace yq {
    GGraph::GGraph() = default;
    GGraph::GGraph(create_k) : GGraph(new GDocument(NEW), 0) {}

    GGraph::GGraph(const GGraph&) = default;
    GGraph::GGraph(GGraph&&) = default;
    GGraph::GGraph(GDocumentPtr doc, gid_t i) : GBase(doc, i) {}
    GGraph::~GGraph() = default;
    GGraph& GGraph::operator=(const GGraph&) = default;
    GGraph& GGraph::operator=(GGraph&&) = default;

    GGraph::operator bool() const
    {
        return static_cast<bool>(data());
    }

    GGraphData*  GGraph::data()
    {
        if(m_doc)
            return m_doc -> graph(m_id);
        return nullptr;
    }
    
    const GGraphData*  GGraph::data() const
    {
        if(m_doc)
            return m_doc -> graph(m_id);
        return nullptr;
    }

    std::vector<GEdge> GGraph::edges() const
    {
        std::vector<GEdge> ret;
        if(m_doc){
            m_doc->edges(FOR, [&](const GEdgeData& d){
                ret.push_back(GEdge(m_doc, d.id));
            });
        }
        return ret;
    }
    
    size_t             GGraph::edges(count_k) const
    {
        size_t ret = 0;
        if(m_doc){
            m_doc -> edges(FOR, [&](const GEdgeData& d){
                if(d.parent == m_id)
                    ++ret;
            });
        }
        return ret;
    }

    GNode   GGraph::node(create_k)
    {
        if(!m_doc)
            return GNode();
        GNodeData* d    = m_doc->node(CREATE);
        d->parent   = m_id;
        return GNode(m_doc, d->id); 
    }

    GNode              GGraph::node(create_k, const GNodeTemplate& nt)
    {
        if(!m_doc)
            return GNode();
        GNodeData*  d   = m_doc->node(CREATE);
        d->parent           = m_id;
        d->node_template    = to_string(nt.url());
        return GNode(m_doc, d->id);
    }

    std::vector<GNode> GGraph::nodes() const
    {
        std::vector<GNode> ret;
        if(m_doc){
            m_doc->nodes(FOR, [&](const GNodeData& d){
                ret.push_back(GNode(m_doc, d.id));
            });
        }
        return ret;
    }
    
    size_t      GGraph::nodes(count_k) const
    {
        size_t ret = 0;
        if(m_doc){
            m_doc -> nodes(FOR, [&](const GNodeData& d){
                if(d.parent == m_id)
                    ++ret;
            });
        }
        return ret;
    }
}
