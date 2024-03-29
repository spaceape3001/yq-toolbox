////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "UniqueID.hpp"
#include <atomic>

namespace yq {
    UniqueID::UniqueID()
    {
        static std::atomic<uint64_t>    last{0};
        m_id    = ++last;
    }
}
