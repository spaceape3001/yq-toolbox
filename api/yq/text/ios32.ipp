////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "ios32.hpp"
#include <yq/text/format.hpp>

namespace yq {
}

namespace std {
    ostream& operator<<(ostream& out, u32string_view sv)
    {
        for(char32_t ch : sv)
            out << yq::to_string_view(ch);
        return out;
    }

    ostream& operator<<(ostream& out, const u32string& s)
    {
        return out << (u32string_view) s;
    }
}

