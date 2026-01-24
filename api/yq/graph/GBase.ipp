////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GBase.hpp"
#include "GBaseData.hpp"
#include "GDocument.hpp"
#include "GEdge.hpp"
#include "GGraph.hpp"
#include "GLine.hpp"
#include "GNode.hpp"
#include "GPort.hpp"
#include "GShape.hpp"
#include "GText.hpp"

namespace yq {
    GBase::GBase() = default;
    GBase::GBase(const GBase&) = default;
    GBase::GBase(GBase&&) = default;
    GBase::~GBase() = default;
    GBase::GBase(GDocumentPtr gp, uint64_t ip) : m_doc(gp), m_id(ip) {}

    GBase&  GBase::operator=(const GBase&) = default;
    GBase&  GBase::operator=(GBase&&) = default;

    GBase::operator GEdge() const
    {
        if(is_edge())
            return GEdge(m_doc, m_id);
        return GEdge();
    }

    GBase::operator GGraph() const
    {
        if(is_graph())
            return GGraph(m_doc, m_id);
        return GGraph();
    }

    GBase::operator GLine() const
    {
        if(is_line())
            return GLine(m_doc, m_id);
        return GLine();
    }

    GBase::operator GNode() const
    {
        if(is_node())
            return GNode(m_doc, m_id);
        return GNode();
    }
    
    GBase::operator GPort() const
    {
        if(is_port())
            return GPort(m_doc, m_id);
        return GPort();
    }
    
    GBase::operator GShape() const
    {
        if(is_shape())
            return GShape(m_doc, m_id);
        return GShape();
    }
    
    GBase::operator GText() const
    {
        if(is_text())
            return GText(m_doc, m_id);
        return GText();
    }

    GBase::operator bool() const
    {
        return static_cast<bool>(data());
    }

    GBaseData*          GBase::data()
    {
        if(!m_doc)
            return nullptr;
        return m_doc -> data(m_id);
    }
    
    const GBaseData*    GBase::data() const
    {
        if(!m_doc)
            return nullptr;
        return m_doc -> data(m_id);
    }

    GDocumentPtr    GBase::document() 
    { 
        return m_doc; 
    }
    
    GDocumentCPtr   GBase::document() const 
    { 
        return m_doc; 
    }

    bool    GBase::is_edge() const
    {
        if(const GBaseData* d = data())
            return d->is_edge();
        return false;
    }
    
    bool    GBase::is_deleted() const
    {
        if(const GBaseData* d = data())
            return d->deleted;
        return false;
    }
    
    bool    GBase::is_graph() const
    {
        if(const GBaseData* d = data())
            return d->is_graph();
        return false;
    }
    
    bool    GBase::is_line() const
    {
        if(const GBaseData* d = data())
            return d->is_line();
        return false;
    }
    
    bool    GBase::is_node() const
    {
        if(const GBaseData* d = data())
            return d->is_node();
        return false;
    }
    
    bool    GBase::is_port() const
    {
        if(const GBaseData* d = data())
            return d->is_port();
        return false;
    }
    
    bool    GBase::is_shape() const
    {
        if(const GBaseData* d = data())
            return d->is_shape();
        return false;
    }
    
    bool    GBase::is_text() const
    {
        if(const GBaseData* d = data())
            return d->is_text();
        return false;
    }
}
