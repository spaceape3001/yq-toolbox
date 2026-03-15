////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/physics/state/DState20.hpp>
#include <yq/physics/state/KState21.hpp>
#include <yq/physics/state/PTime.hpp>

namespace yq::physics {
    struct DState21 : public PTime, public KState21 {
        constexpr operator DState20& () noexcept { return *reinterpret_cast<DState20*>(this); }
        constexpr operator const DState20& () const noexcept { return *reinterpret_cast<const DState20*>(this); }
    };
}
