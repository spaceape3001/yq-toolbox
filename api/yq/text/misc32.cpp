////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "misc32.hpp"

namespace yq {
    std::u32string&    set_if_empty(std::u32string&a, std::u32string_view b, bool fOverride)
    {
        if((a.empty() || fOverride) && !b.empty())
            a  = b;
        return a;
    }
    
}
