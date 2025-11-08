////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "XCase.hpp"
#include <cstring>

namespace yq {
    bool    XCase::operator()(const char*a, const char*b) const
    {
        if(!a)
            return b && *b;
        if(!b)
            return !(a && *a);
        return strcmp(a, b) < 0;
    }
}
