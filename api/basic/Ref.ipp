////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Ref.hpp"

namespace yq {

    RefCount::RefCount()
    {
        m_count     = 0;
    }

    RefCount::RefCount(const RefCount&)
    {
        m_count     = 0;
    }

    void	RefCount::incRef() const
    {
        ++m_count;
    }

    void	RefCount::decRef() const
    {
        if(!--m_count) 
            delete this;
    }
}
