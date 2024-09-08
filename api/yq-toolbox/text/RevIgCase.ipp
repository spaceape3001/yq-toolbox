////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq-toolbox/text/RevIgCase.hpp>
#include <yq-toolbox/text/chars.hpp>
#include <yq-toolbox/text/chars32.hpp>
#include <yq-toolbox/text/match.hpp>
#include <yq-toolbox/text/match32.hpp>

namespace yq {

    bool    RevIgCase::operator()(const std::string_view&a, const std::string_view&b) const
    {
        return is_greater_igCase(a,b);
    }

    bool    RevIgCase::operator()(const std::u32string_view&a, const std::u32string_view&b) const
    {
        return is_greater_igCase(a,b);
    }

    bool    RevIgCase::operator()(char a, char b) const
    {
        return to_lower(a) > to_lower(b);
    }
    
    bool    RevIgCase::operator()(char32_t a, char32_t b) const
    {
        return to_lower(a) > to_lower(b);
    }

}
