////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "MaybeCase.hpp"
#include <0/basic/TextUtils.hpp>
#include <0/basic/TextUtils32.hpp>

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
