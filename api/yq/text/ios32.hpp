////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <string_view>
#include <iosfwd>

namespace std {
    ostream& operator<<(ostream&, u32string_view);
    ostream& operator<<(ostream&, const u32string&);
}
