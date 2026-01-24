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
}
