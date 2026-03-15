////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/physics/state/DState30.hpp>
#include <yq/physics/state/DState31.hpp>
#include <yq/physics/state/KState32.hpp>
#include <yq/physics/state/PTime.hpp>

namespace yq::physics {
    struct DState32 : public PTime, public KState32 {
        constexpr operator DState30& () noexcept { return *reinterpret_cast<DState30*>(this); }
        constexpr operator const DState30& () const noexcept { return *reinterpret_cast<const DState30*>(this); }
        constexpr operator DState31& () noexcept { return *reinterpret_cast<DState31*>(this); }
        constexpr operator const DState31& () const noexcept { return *reinterpret_cast<const DState31*>(this); }
    };
}
