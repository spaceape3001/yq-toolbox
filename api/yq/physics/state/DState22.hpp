////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/physics/state/DState20.hpp>
#include <yq/physics/state/DState21.hpp>
#include <yq/physics/state/KState22.hpp>
#include <yq/physics/state/PTime.hpp>

namespace yq::physics {
    struct DState22 : public PTime, public KState22 {
        constexpr operator DState20& () noexcept { return *reinterpret_cast<DState20*>(this); }
        constexpr operator const DState20& () const noexcept { return *reinterpret_cast<const DState20*>(this); }
        constexpr operator DState21& () noexcept { return *reinterpret_cast<DState21*>(this); }
        constexpr operator const DState21& () const noexcept { return *reinterpret_cast<const DState21*>(this); }
    };
}
