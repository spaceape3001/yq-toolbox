////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <yq/meta/MetaBinder.hpp>

namespace yq {
    //! This is the user expression (for any/meta binding purposes)
    struct AlgebraString {
        std::string     algebra;
        constexpr auto operator<=>(const AlgebraString&) const noexcept = default;
    };
}

YQ_TYPE_DECLARE(yq::AlgebraString)
