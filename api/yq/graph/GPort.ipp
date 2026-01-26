////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

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
