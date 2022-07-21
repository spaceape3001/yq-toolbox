////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Revision.hpp"

namespace yq {
    Revision::Revision(Revision* m)
    {
        m_revision      = 0;
        m_master        = m;
    }
    
    void        Revision::changed()
    {
        ++m_revision;
        if(m_master)
            m_master->changed();
    }
}

