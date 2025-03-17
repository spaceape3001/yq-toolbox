////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>
#include <yq/meta/InfoBinder.hpp>

namespace yq::spatial {
    struct ID {
        using id_t      = uint32_t;
        id_t    id  = {};
        constexpr operator id_t () const noexcept { return id; }
        constexpr auto operator<=>(const ID&) const noexcept = default;
    };
}

YQ_TYPE_DECLARE(yq::spatial::ID)
