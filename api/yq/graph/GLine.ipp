////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GLine.hpp"
#include "GDocument.hpp"

namespace yq {
    GLine::GLine() = default;
    GLine::GLine(const GLine&) = default;
    GLine::GLine(GLine&&) = default;

    GLine::GLine(GDocumentPtr doc, gid_t i) : GBase(doc, i)
    {
    }
    
    GLine::~GLine() = default;
    
    GLine& GLine::operator=(const GLine&) = default;
    GLine& GLine::operator=(GLine&&) = default;
    
    GLine::operator bool() const
    {
        return static_cast<bool>(data());
    }

    GLineData*          GLine::data()
    {
        if(m_doc)
            return m_doc -> line(m_id);
        return nullptr;
    }
    
    const GLineData*    GLine::data() const
    {
        if(m_doc)
            return m_doc -> line(m_id);
        return nullptr;
    }

}

