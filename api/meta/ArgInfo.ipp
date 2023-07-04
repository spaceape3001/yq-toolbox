////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <meta/ArgInfo.hpp>

namespace yq {
    ArgInfo::ArgInfo(const std::source_location& sl, const Meta&t, Meta*par) : 
        Meta({}, par, sl), m_type(t), m_default(nullptr)
    {
        set(Flag::ARG);
    }
}
