////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "RevIgCase.hpp"
#include <basic/TextUtils.hpp>

namespace yq {

    bool    RevIgCase::operator()(const std::string_view&a, const std::string_view&b) const
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
