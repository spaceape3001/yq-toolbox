////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GNode.hpp"
#include "GNodeData.hpp"
#include "GPort.hpp"
#include "GPortData.hpp"
#include "GDocument.hxx"

namespace yq {
    GNode::GNode() = default;
    GNode::GNode(const GNode&) = default;
    GNode::GNode(GNode&&) = default;
    GNode::GNode(GDocumentPtr doc, gid_t i) : GBase(doc, i) {}
    GNode::~GNode() = default;
    GNode& GNode::operator=(const GNode&) = default;
    GNode& GNode::operator=(GNode&&) = default;

    GNode::operator bool() const
    {
        return static_cast<bool>(data());
    }

    GNodeData*          GNode::data()
    {
        if(m_doc)
            return m_doc -> node(m_id);
        return nullptr;
    }
    
    const GNodeData*    GNode::data() const
    {
        if(m_doc)
            return m_doc -> node(m_id);
        return nullptr;
    }

    std::string_view    GNode::node_template() const
    {
        if(const GNodeData* gn = data()){
            return gn -> node_template;
        } else
            return {};
    }

    std::vector<GPort>  GNode::ports() const
    {
        std::vector<GPort>  ret;
        if(m_doc){
            m_doc -> ports(FOR, [&](const GPortData& d){
                if(d.parent == m_id)
                    ret.push_back(GPort(m_doc, d.id));
            });
        }
        return ret;
    }
    
    size_t              GNode::ports(count_k) const
    {
        size_t ret = 0;
        if(m_doc){
            m_doc -> ports(FOR, [&](const GPortData& d){
                if(d.parent == m_id)
                    ++ret;
            });
        }
        return ret;
    }

    Vector2F  GNode::position() const
    {
        if(const GNodeData* gn = data())
            return gn -> position;
        return NAN;
    }
    
    void      GNode::position(set_k, const Vector2F&v)
    {
        if(GNodeData* gn = data())
            gn -> position  = v;
    }

    ////////////////////////////////////////////////////////////////////////////

    GNodeData::GNodeData(gid_t _id) : GBaseData(_id) {}
    
    GNodeData::GNodeData(const GNodeData& cp ) : GBaseData(cp), 
        node_template(cp.node_template),
        position(cp.position),
        size(cp.size)
    {
    }
    
    GNodeData::~GNodeData(){}
    
    GBaseData*  GNodeData::clone() const 
    { 
        return new GNodeData(*this); 
    }
}
