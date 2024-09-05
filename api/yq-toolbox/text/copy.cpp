////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "copy.hpp"
#include <yq-toolbox/text/IgCase.hpp>

namespace yq {

    string_set_t        copy(const string_view_set_t&input)
    {
        string_set_t    ret;
        for(auto& s : input)
            ret.insert(copy(s));
        return ret;
    }

    std::vector<std::string>    copy(const std::vector<std::string>&input)
    {
        std::vector<std::string>    ret;
        ret.reserve(input.size());
        for(const std::string& s : input)
            ret.push_back(s);
        return ret;
    }
    
    std::vector<std::string>    copy(const std::vector<std::string_view>&input)
    {
        std::vector<std::string>    ret;
        ret.reserve(input.size());
        for(std::string_view s : input)
            ret.push_back(std::string(s));
        return ret;
    }

    std::vector<std::string>  copy(std::initializer_list<std::string_view> input)
    {
        std::vector<std::string>    ret;
        ret.reserve(input.size());
        for(std::string_view s : input)
            ret.push_back(std::string(s));
        return ret;
    }
}
