////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/meta/AnyDef.hpp>
#include <basic/meta/InfoBinder.hpp>
#include <basic/meta/TypeInfo.hpp>
#include <basic/meta/AnyImpl.hpp>

namespace yq {

    boolean_r   to_boolean(const Any&);
    double_r    to_double(const Any&);
    float_r     to_float(const Any&);
    int_r       to_int(const Any&);
    int8_r      to_int8(const Any&);
    int16_r     to_int16(const Any&);
    int32_r     to_int32(const Any&);
    int64_r     to_int64(const Any&);
    integer_r   to_integer(const Any&);
    short_r     to_short(const Any&);
    string_r    to_string(const Any&);
    uint8_r     to_uint8(const Any&);
    uint16_r    to_uint16(const Any&);
    uint32_r    to_uint32(const Any&);
    uint64_r    to_uint64(const Any&);
    unsigned_r  to_uinteger(const Any&);
    ushort_r    to_ushort(const Any&);
}

