////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/physics/state/DState30.hpp>
#include <yq/physics/state/KState31.hpp>
#include <yq/physics/state/PTime.hpp>
\
namespace yq::physics {
    struct DState31 : public PTime, public KState31 {
        constexpr operator DState30& () noexcept { return *reinterpret_cast<DState30*>(this); }
        constexpr operator const DState30& () const noexcept { return *reinterpret_cast<const DState30*>(this); }
    };
}
