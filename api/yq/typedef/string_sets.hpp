////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <set>
#include <string>
#include <string_view>
#include <yq-toolbox/container/forward.hpp>

namespace yq {
    struct IgCase;

    using StringSet                 = Set<std::string,IgCase>;
    using StringViewSet             = Set<std::string_view,IgCase>;

    using string_set_t              = std::set<std::string,IgCase>;
    using string_xset_t             = std::set<std::string>;
    using string_view_set_t         = std::set<std::string_view,IgCase>;
    using string_view_xset_t        = std::set<std::string_view>;

    using U32StringViewSet          = Set<std::u32string_view, IgCase>;

    using u32string_set_t           = std::set<std::u32string,IgCase>;
    using u32string_view_set_t      = std::set<std::u32string_view,IgCase>;
}
