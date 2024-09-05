////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <yq-toolbox/container/forward.hpp>

namespace yq {
    using StringViewVector          = Vector<std::string_view>;

    using string_vector_t           = std::vector<std::string>;
    using string_view_vector_t      = std::vector<std::string_view>;

    using u32string_vector_t        = std::vector<std::u32string>;
    using u32string_view_vector_t   = std::vector<std::u32string_view>;
}
