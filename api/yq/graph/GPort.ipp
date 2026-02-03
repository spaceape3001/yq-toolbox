////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GNode.hpp"
#include "GPort.hpp"
#include "GPortData.hpp"

namespace yq {
    GPort::GPort() = default;
    GPort::GPort(const GPort&) = default;
    GPort::GPort(GPort&&) = default;
    GPort::GPort(GDocumentPtr doc, gid_t i) : GBase(doc, i) {}
    GPort::~GPort() = default;
    GPort& GPort::operator=(const GPort&) = default;
    GPort& GPort::operator=(GPort&&) = default;

    GPort::operator bool() const
    {
        return static_cast<bool>(data());
    }

    GPortData*  GPort::data()
    {
        if(m_doc)
            return m_doc -> port(m_id);
        return nullptr;
    }
    
    const GPortData*  GPort::data() const
    {
        if(m_doc)
            return m_doc -> port(m_id);
        return nullptr;
    }

    bool    GPort::is_input() const
    {
        if(const GPortData* d = data())
            return d -> input;
        return false;
    }
    
    bool    GPort::is_output() const
    {
        if(const GPortData* d = data())
            return d -> output;
        return false;
    }
    
    GNode   GPort::node() const
    {
        if(const GPortData* d = data()){
            if(m_doc -> is_node(d->parent))
                return GNode(m_doc, d->parent);
        }
        return GNode();
    }

    ////////////////////////////////////////////////////////////////////////////

    GPortData::GPortData(gid_t _id) : GBaseData(_id) {}
    GPortData::GPortData(const GPortData& cp) : GBaseData(cp)
    {
    }
    
    GPortData::~GPortData(){}
    
    GBaseData*  GPortData::clone() const 
    { 
        return new GPortData(*this); 
    }
}
