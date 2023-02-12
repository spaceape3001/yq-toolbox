////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/meta/ArgInfo.hpp>

namespace yq {
    ArgInfo::ArgInfo(const std::source_location& sl, const Meta&t, Meta*par, options_t opts) : 
        Meta({}, par, sl), m_type(t), m_default(nullptr)
    {
        m_flags |= ARG;
        set_options(opts);
    }
}
