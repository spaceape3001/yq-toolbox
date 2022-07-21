////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "IgCase.hpp"
#include <basic/TextUtils.hpp>

namespace yq {

    bool    IgCase::operator()(const std::string_view&a, const std::string_view&b) const
    {
        return is_less_igCase(a,b);
    }


    bool    IgCase::operator()(char a, char b) const
    {
        return to_lower(a) < to_lower(b);
    }
    
    bool    IgCase::operator()(char32_t a, char32_t b) const
    {
        return to_lower(a) < to_lower(b);
    }

}
