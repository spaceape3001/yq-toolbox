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
    template <typename T> struct BasicUrl;
    using UrlView       = BasicUrl<std::string_view>;
    using Url           = BasicUrl<std::string>;
    using Url32         = BasicUrl<std::u32string>;
    using Url32View     = BasicUrl<std::u32string_view>;
    
    YQ_VIEW_TYPE(Url, UrlView)
    YQ_VIEW_TYPE(Url32, Url32View)
}
