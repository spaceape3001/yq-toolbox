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

#include "GDocument.hxx"

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

    std::vector<GBase>  GBase::children() const
    {
        std::vector<GBase>  ret;
        if(m_doc){
            m_doc -> datas(FOR, [&](const GBaseData&d) {
                if(d.parent == m_id)
                    ret.push_back(GBase(m_doc, d.id));
            });
        }
        return ret;
    }
    
    size_t              GBase::children(count_k) const
    {
        size_t ret = 0;
        if(m_doc){
            m_doc -> datas(FOR, [&](const GBaseData&) {
                ++ret;
            });
        }
        return ret;
    }

    bool                GBase::deleted() const
    {
        if(const GBaseData* d = data())
            return d->deleted;
        return true;
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

    Tristate  GBase::hidden() const
    {
        if(const GBaseData* d = data())
            return d->hidden;
        return Tristate::Inherit;
    }
    
    void      GBase::hidden(set_k, Tristate v)
    {
        if(GBaseData* d = data())
            d -> hidden = v;
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

    GBase   GBase::parent() const
    {
        if(const GBaseData* d = data())
            return GBase(m_doc, d->parent);
        return GBase();
    }
    
    double  GBase::z() const
    {
        if(const GBaseData* d = data())
            return d -> z;
        return NAN;
    }
    
    void    GBase::z(set_k, double v)
    {
        if(GBaseData* d = data())
            d -> z = v;
    }

    ////////////////////////////////////////////////////////////////////////////

    GBaseData::GBaseData(gid_t _id) : id(_id) 
    {
    }

    GBaseData::GBaseData(const GBaseData& cp) : 
        id(cp.id), 
        deleted(cp.deleted),    // should be skipping...maybe...
        hidden(cp.hidden), 
        parent(cp.parent), 
        z(cp.z) 
    {
    }

    GBaseData::~GBaseData()
    {
    }

    ////////////////////////////////////////////////////////////////////////////

    GPosSizeData::GPosSizeData()
    {
    }
    
    GPosSizeData::GPosSizeData(const GPosSizeData& cp) :         
        position(cp.position),
        size(cp.size)
    {
    }
    
    GPosSizeData::~GPosSizeData()
    {
    }
    
}
