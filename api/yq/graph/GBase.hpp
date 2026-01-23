////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/typedef/g_document.hpp>

namespace yq::graph {

    //! Root to graph things... pointer to document & ID
    class GBase {
    public:
    
    protected:
        GBase();
        GBase(GDocumentPtr, uint64_t);
        GBase(const GBase&);
        GBase(GBase&&);
        ~GBase();
    
    private:
        GDocumentPtr    m_doc;
        uint64_t        m_id    = 0;
    };
}
