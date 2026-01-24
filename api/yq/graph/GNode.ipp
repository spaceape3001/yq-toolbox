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
    GNode::GNode(GDocumentPtr doc, gid_t i) : GText(doc, i) {}
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
}
