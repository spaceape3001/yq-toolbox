////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GText.hpp"
#include "GTextData.hpp"

namespace yq {
    GText::GText() = default;
    GText::GText(const GText&) = default;
    GText::GText(GText&&) = default;
    GText::GText(GDocumentPtr doc, gid_t i) : GBase(doc, i) {}
    GText::~GText() = default;
    GText& GText::operator=(const GText&) = default;
    GText& GText::operator=(GText&&) = default;

    GText::operator bool() const
    {
        return static_cast<bool>(data());
    }

    GTextData*  GText::data()
    {
        if(m_doc)
            return m_doc -> text(m_id);
        return nullptr;
    }
    
    const GTextData*  GText::data() const
    {
        if(m_doc)
            return m_doc -> text(m_id);
        return nullptr;
    }

    Vector2F  GText::position() const
    {
        if(const GTextData* gn = data())
            return gn -> position;
        return NAN;
    }
    
    void      GText::position(set_k, const Vector2F&v)
    {
        if(GTextData* gn = data())
            gn -> position  = v;
    }

    ////////////////////////////////////////////////////////////////////////////

    GTextData::GTextData(gid_t _id) : GBaseData(_id) {}
    GTextData::GTextData(const GTextData& cp) : 
        GBaseData(cp), position(cp.position), size(cp.size), symbol(cp.symbol), text(cp.text)
    {
    }
    
    GTextData::~GTextData(){}
    GBaseData*  GTextData::clone() const 
    { 
        return new GTextData(*this); 
    }
}
