////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <span>
#include <yq/trait/has_equality.hpp>

namespace yq {
    template <typename T>
    bool    is_in(T val, std::span<const T> vals)
    {
        static_assert(has_equality_v<T>, "Type needs to have an equality operator!");
        for(auto& t : vals)
            if(val == t)
                return true;
        return false;
    }
}
