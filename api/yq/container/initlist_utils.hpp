////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <initializer_list>

namespace yq {
    template <typename T>
    bool    is_in(T val, std::initializer_list<T> vals)
    {
        for(auto& t : vals)
            if(val == t)
                return true;
        return false;
    }
}
