////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/MetaBinder.hpp>
#include <string>

namespace yq {
    struct Vector1S {
        std::string x;
        constexpr auto operator<=>(const Vector1S&) const = default;
    };
}

YQ_TYPE_DECLARE(yq::Vector1S)

