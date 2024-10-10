////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "copy32.hpp"
#include <yq/text/IgCase.hpp>

namespace yq {
    u32string_set_t        copy(const u32string_view_set_t&input)
    {
        u32string_set_t    ret;
        for(auto& s : input)
            ret.insert(copy(s));
        return ret;
    }

    std::vector<std::u32string>    copy(const std::vector<std::u32string>&input)
    {
        std::vector<std::u32string>    ret;
        ret.reserve(input.size());
        for(const std::u32string& s : input)
            ret.push_back(s);
        return ret;
    }
    
    std::vector<std::u32string>    copy(const std::vector<std::u32string_view>&input)
    {
        std::vector<std::u32string>    ret;
        ret.reserve(input.size());
        for(std::u32string_view s : input)
            ret.push_back(std::u32string(s));
        return ret;
    }

    std::vector<std::u32string>  copy(std::initializer_list<std::u32string_view> input)
    {
        std::vector<std::u32string>    ret;
        ret.reserve(input.size());
        for(std::u32string_view s : input)
            ret.push_back(std::u32string(s));
        return ret;
    }
}
