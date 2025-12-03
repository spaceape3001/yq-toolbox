////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <string_view>
#include <map>
#include <yq/container/forward.hpp>
#include <yq/typedef/url.hpp>

namespace yq {
    struct IgCase;
    class Any;

    using StringMap                 = Map<std::string,std::string,IgCase>;
    using StringViewMap             = Map<std::string_view,std::string_view,IgCase>;
    
    using StringMultiMap            = MultiMap<std::string,std::string,IgCase>;
    using StringViewMultiMap        = MultiMap<std::string_view,std::string_view,IgCase>;

    using StringAnyMap              = Map<std::string,Any,IgCase>;
    using StringAnyMultiMap         = MultiMap<std::string,Any,IgCase>;

    using string_u64_xmap_t         = std::map<std::string,uint64_t>;
    using string_u64_xmmap_t        = std::multimap<std::string,uint64_t>;

    using string_url_xmap_t         = std::map<std::string,Url>;
    using string_url_xmmap_t        = std::multimap<std::string,Url>;

    using string_any_xmap_t         = std::map<std::string,Any>;
    using string_any_map_t          = std::map<std::string,Any,IgCase>;
    using string_any_multimap_t     = std::multimap<std::string,Any,IgCase>;
    using string_view_any_map_t     = std::map<std::string_view,Any,IgCase>;

    using string_map_t              = std::map<std::string,std::string,IgCase>;
    using string_view_map_t         = std::map<std::string_view,std::string_view,IgCase>;

    using u32string_any_map_t       = std::map<std::u32string,Any,IgCase>;
    using u32string_map_t           = std::map<std::u32string,std::u32string,IgCase>;
}
