////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <string_view>

namespace yq {
    template <typename T> struct BasicUrl;
    using UrlView       = BasicUrl<std::string_view>;
    using Url           = BasicUrl<std::string>;
    using Url32         = BasicUrl<std::u32string>;
    using Url32View     = BasicUrl<std::u32string_view>;
}
