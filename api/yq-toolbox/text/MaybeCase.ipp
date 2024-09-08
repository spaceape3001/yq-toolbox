////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq-toolbox/text/MaybeCase.hpp>
#include <yq-toolbox/text/chars.hpp>
#include <yq-toolbox/text/chars32.hpp>
#include <yq-toolbox/text/match.hpp>
#include <yq-toolbox/text/match32.hpp>

namespace yq {
    bool    MaybeCase::operator()(const std::u32string_view& a, const std::u32string_view& b) const
    {
        return igCase ? is_less_igCase(a,b) : (a<b);
    }

    bool    MaybeCase::operator()(const std::string_view& a, const std::string_view& b) const
    {
        return igCase ? is_less_igCase(a,b) : (a<b);
    }


    bool    MaybeCase::operator()(char a, char b) const
    {
        return igCase ? (to_lower(a) < to_lower(b)) : (a < b);
    }
    
    bool    MaybeCase::operator()(char32_t a, char32_t b) const
    {
        return igCase ? (to_lower(a) < to_lower(b)) : (a < b);
    }

}
