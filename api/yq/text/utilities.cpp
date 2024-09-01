////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/text/utilities.hpp>
#include <cuchar>
#include <cwchar>

namespace yq {
    std::string&  operator+=(std::string&str, char32_t ch)
    {
        std::mbstate_t  state{};
        char            buffer[MB_CUR_MAX+1];
        int len = (int) c32rtomb(buffer, ch, &state);
        if(len > 0)
            str.append(buffer, len);
        return str;
    }
}
