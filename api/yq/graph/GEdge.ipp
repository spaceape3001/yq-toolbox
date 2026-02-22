////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GEdge.hpp"
#include "GEdgeData.hpp"
#include "GDocument.hpp"

namespace yq {
    
    GEdge::GEdge() = default;
    GEdge::GEdge(const GEdge&) = default;
    GEdge::GEdge(GEdge&&) = default;
    GEdge::GEdge(GDocumentPtr doc, gid_t i) : GBase(doc, i)
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
        if(const GEdgeData* ge = data(); ge->source)
            return GBase(m_doc, ge->source);
        return GBase();
    }

    GNode  GEdge::source(node_k) const
    {
        if(const GEdgeData* ge = data(); ge->source){
            if(m_doc->is_node(ge->source)){
                return GNode(m_doc, ge->source);
            }
            if(const GPortData* gp = m_doc->port(ge->source)){
                if(m_doc->is_node(gp->parent))
                    return GNode(m_doc, gp->parent);
            }
        }
        return GNode();
    }
    
    GPort  GEdge::source(port_k) const
    {
        if(const GEdgeData* ge = data(); ge->source){
            if(m_doc->is_port(ge->source))
                return GPort(m_doc, ge->source);
        }
        return GPort();
    }
    
    GBase  GEdge::target() const
    {
        if(const GEdgeData* ge = data(); ge->target)
            return GBase(m_doc, ge->target);
        return GBase();
    }

    GNode  GEdge::target(node_k) const
    {
        if(const GEdgeData* ge = data(); ge->target){
            if(m_doc->is_node(ge->target)){
                return GNode(m_doc, ge->target);
            }
            if(const GPortData* gp = m_doc->port(ge->target)){
                if(m_doc->is_node(gp->parent))
                    return GNode(m_doc, gp->parent);
            }
        }
        return GNode();
    }
    
    GPort  GEdge::target(port_k) const
    {
        if(const GEdgeData* ge = data(); ge->target){
            if(m_doc->is_port(ge->target))
                return GPort(m_doc, ge->target);
        }
        return GPort();
    }

    ////////////////////////////////////////////////////////////////////////////

    GEdgeData::GEdgeData(gid_t _id) : GBaseData(_id) {}

    GEdgeData::GEdgeData(const GEdgeData& cp ) : GBaseData(cp), 
        source(cp.source), 
        target(cp.target), 
        waypoints(cp.waypoints) 
    {
    }

    GEdgeData::~GEdgeData(){}

    GBaseData*  GEdgeData::clone() const 
    { 
        return new GEdgeData(*this); 
    }
}
