////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GEdge.hpp"
#include "GDocument.hpp"

namespace yq {
    
    GEdge::GEdge() = default;
    GEdge::GEdge(const GEdge&) = default;
    GEdge::GEdge(GEdge&&) = default;
    GEdge::GEdge(GDocumentPtr doc, gid_t i) : GLine(doc, i)
    {
    }
    
    GEdge::~GEdge() = default;
    
    GEdge& GEdge::operator=(const GEdge&) = default;
    GEdge& GEdge::operator=(GEdge&&) = default;
    
    GEdge::operator bool() const
    {
        return static_cast<bool>(data());
    }

    GEdgeData*          GEdge::data()
    {
        if(m_doc)
            return m_doc -> edge(m_id);
        return nullptr;
    }
    
    const GEdgeData*    GEdge::data() const
    {
        if(m_doc)
            return m_doc -> edge(m_id);
        return nullptr;
    }

    GBase  GEdge::source() const
    {
        if(const GEdgeData* ge = data(); !ge->waypoints.empty()){
            if(auto p = std::get_if<gid_t>(&ge->waypoints.front().position)){
                return GBase(m_doc, *p);
            }
        }
        return GBase();
    }
    
    GBase  GEdge::target() const
    {
        if(const GEdgeData* ge = data(); (ge->waypoints.size() > 1)){
            if(auto p = std::get_if<gid_t>(&ge->waypoints.back().position)){
                return GBase(m_doc, *p);
            }
        }
        return GBase();
    }
}
