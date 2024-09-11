////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <string_view>
#include <initializer_list>

namespace yq {
    using string_view_initializer_list_t        = std::initializer_list<std::string_view>;
    using u32string_view_initializer_list_t     = std::initializer_list<std::u32string_view>;
    using char_p_seq_t                          = std::initializer_list<const char*>;
}
