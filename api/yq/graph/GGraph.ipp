////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GGraph.hpp"
#include "GGraphData.hpp"

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
}
