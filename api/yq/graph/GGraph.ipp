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

    GGraph::GGraph(load_k, std::string_view sv)
    {
        GDocumentCPtr doc = GDocument::IO::load(sv);
        m_doc   = const_cast<GDocument*>(doc.ptr());
    }
    
    GGraph::GGraph(read_only_k, GDocumentCPtr doc)
    {
        if(doc && doc->read_only())
            m_doc   = const_cast<GDocument*>(doc.ptr());
    }

    GGraph::operator bool() const
    {
        return static_cast<bool>(data());
    }

    GEdge   GGraph::connect(const GNode&src, const GNode&tgt)
    {
        if(!m_doc)
            return {};
        if(m_doc->read_only())
            return {};
        if(src.document().ptr() != m_doc)
            return {};
        if(tgt.document().ptr() != m_doc)
            return {};
        GEdgeData* ge   = m_doc->connect(src.id(), tgt.id());
        if(!ge)
            return {};
        return GEdge(m_doc, ge->id);
    }
    
    GEdge   GGraph::connect(const GNode&src, const GPort&tgt)
    {
        if(!m_doc)
            return {};
        if(m_doc->read_only())
            return {};
        if(src.document().ptr() != m_doc)
            return {};
        if(tgt.document().ptr() != m_doc)
            return {};
        GEdgeData* ge   = m_doc->connect(src.id(), tgt.id());
        if(!ge)
            return {};
        return GEdge(m_doc, ge->id);
    }
    
    GEdge   GGraph::connect(const GPort&src, const GNode&tgt)
    {
        if(!m_doc)
            return {};
        if(m_doc->read_only())
            return {};
        if(src.document().ptr() != m_doc)
            return {};
        if(tgt.document().ptr() != m_doc)
            return {};
        GEdgeData* ge   = m_doc->connect(src.id(), tgt.id());
        if(!ge)
            return {};
        return GEdge(m_doc, ge->id);
    }
    
    GEdge   GGraph::connect(const GPort&src, const GPort&tgt)
    {
        if(!m_doc)
            return {};
        if(m_doc->read_only())
            return {};
        if(src.document().ptr() != m_doc)
            return {};
        if(tgt.document().ptr() != m_doc)
            return {};
        GEdgeData* ge   = m_doc->connect(src.id(), tgt.id());
        if(!ge)
            return {};
        return GEdge(m_doc, ge->id);
    }
    
    bool    GGraph::connected(const GNode&src, const GNode&tgt) const
    {
        if(!m_doc)
            return false;
        if(src.document().ptr() != m_doc)
            return false;
        if(tgt.document().ptr() != m_doc)
            return false;
        return m_doc->connected(src.id(), tgt.id());
    }
    
    bool    GGraph::connected(const GNode&src, const GPort&tgt) const
    {
        if(!m_doc)
            return false;
        if(src.document().ptr() != m_doc)
            return false;
        if(tgt.document().ptr() != m_doc)
            return false;
        return m_doc->connected(src.id(), tgt.id());
    }
    
    bool    GGraph::connected(const GPort&src, const GNode&tgt) const
    {
        if(!m_doc)
            return false;
        if(src.document().ptr() != m_doc)
            return false;
        if(tgt.document().ptr() != m_doc)
            return false;
        return m_doc->connected(src.id(), tgt.id());
    }
    
    bool    GGraph::connected(const GPort&src, const GPort&tgt) const
    {
        if(!m_doc)
            return false;
        if(src.document().ptr() != m_doc)
            return false;
        if(tgt.document().ptr() != m_doc)
            return false;
        return m_doc->connected(src.id(), tgt.id());
    }
    
    GEdge   GGraph::connection(const GNode&src, const GNode&tgt) const
    {
        if(!m_doc)
            return {};
        if(src.document().ptr() != m_doc)
            return {};
        if(tgt.document().ptr() != m_doc)
            return {};
        const GEdgeData* ge = m_doc->connection(src.id(), tgt.id());
        if(!ge)
            return {};
        return GEdge(m_doc, ge->id);
    }
    
    GEdge   GGraph::connection(const GNode&src, const GPort&tgt) const
    {
        if(!m_doc)
            return {};
        if(src.document().ptr() != m_doc)
            return {};
        if(tgt.document().ptr() != m_doc)
            return {};
        const GEdgeData* ge = m_doc->connection(src.id(), tgt.id());
        if(!ge)
            return {};
        return GEdge(m_doc, ge->id);
    }
    
    GEdge   GGraph::connection(const GPort&src, const GNode&tgt) const
    {
        if(!m_doc)
            return {};
        if(src.document().ptr() != m_doc)
            return {};
        if(tgt.document().ptr() != m_doc)
            return {};
        const GEdgeData* ge = m_doc->connection(src.id(), tgt.id());
        if(!ge)
            return {};
        return GEdge(m_doc, ge->id);
    }
    
    GEdge   GGraph::connection(const GPort&src, const GPort&tgt) const
    {
        if(!m_doc)
            return {};
        if(src.document().ptr() != m_doc)
            return {};
        if(tgt.document().ptr() != m_doc)
            return {};
        const GEdgeData* ge = m_doc->connection(src.id(), tgt.id());
        if(!ge)
            return {};
        return GEdge(m_doc, ge->id);
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
        if(m_doc->read_only())
            return {};
        GNodeData* d    = m_doc->node(CREATE);
        d->parent   = m_id;
        return GNode(m_doc, d->id); 
    }

    GNode              GGraph::node(create_k, const GNodeTemplate& nt)
    {
        if(!m_doc)
            return GNode();
        if(m_doc->read_only())
            return {};
        GNodeData*  d   = m_doc->node(CREATE);
        d->parent           = m_id;
        d->type             = to_string(nt.url());
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

    ////////////////////////////////////////////////////////////////////////////

    GGraphData::GGraphData(gid_t _id) : GBaseData(_id) {}
    GGraphData::GGraphData(const GGraphData&)  = default;
    GGraphData::~GGraphData() = default;

    GBaseData*  GGraphData::clone() const { return new GGraphData(*this); }

}
