////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <string_view>
#include <utility>

namespace yq {
    class Any;
    
    using StringPair                = std::pair<std::string,std::string>;
    using StringIntPair             = std::pair<std::string,int>;

    using string_any_pair_t         = std::pair<std::string,Any>;
    using string_int_pair_t         = std::pair<std::string,int>;
    using string_pair_t             = std::pair<std::string,std::string>;
    using string_view_pair_t        = std::pair<std::string_view,std::string_view>;

    using u32string_any_pair_t      = std::pair<std::u32string,Any>;
    using u32string_int_pair_t      = std::pair<std::u32string,int>;
    using u32string_pair_t          = std::pair<std::u32string,std::u32string>;
    using u32string_view_pair_t     = std::pair<std::u32string_view,std::u32string_view>;

}
