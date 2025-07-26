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
    struct Algebra {
        std::string     algebra;
        constexpr auto operator<=>(const Algebra&) const noexcept = default;
    };

    inline yq::Algebra operator""_alg(const char* z, unsigned long n) 
    {
        return { std::string(z,n) };
    }
}

YQ_TYPE_DECLARE(yq::Algebra)
