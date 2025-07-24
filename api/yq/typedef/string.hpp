////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <string_view>
#include <yq/trait/view_type.hpp>

namespace yq {
    using std::literals::string_literals::operator""s;
    using std::literals::string_view_literals::operator""sv;

    using string_t      = std::u32string;
    using string_view_t = std::u32string_view;
    
    YQ_VIEW_TYPE(std::string, std::string_view)
    YQ_VIEW_TYPE(std::u32string, std::u32string_view)
}
