////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <string_view>
#include <map>
#include <yq-toolbox/container/forward.hpp>

namespace yq {
    struct IgCase;
    class Any;

    using StringMap                 = Map<std::string,std::string,IgCase>;
    using StringViewMap             = Map<std::string_view,std::string_view,IgCase>;
    
    using StringMultiMap            = MultiMap<std::string,std::string,IgCase>;
    using StringViewMultiMap        = MultiMap<std::string_view,std::string_view,IgCase>;

    using StringAnyMap              = Map<std::string,Any,IgCase>;
    using StringAnyMultiMap         = MultiMap<std::string,Any,IgCase>;

    using string_any_map_t          = std::map<std::string,Any,IgCase>;
    using string_view_any_map_t     = std::map<std::string_view,Any,IgCase>;

    using string_map_t              = std::map<std::string,std::string,IgCase>;
    using u32string_any_map_t       = std::map<std::u32string,Any,IgCase>;
    using u32string_map_t          = std::map<std::u32string,std::u32string,IgCase>;
}
