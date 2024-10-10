////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/AnyDef.hpp>
#include <yq/meta/InfoBinder.hpp>
#include <yq/meta/TypeInfo.hpp>
#include <yq/meta/AnyImpl.hpp>
#include <yq/typedef/expected.hpp>

namespace yq {
    class Any;

    /*! \brief Extract a boolean from Any */
    boolean_x   to_boolean(const Any&);

    /*! \brief Extract a double from Any */
    double_x    to_double(const Any&);

    /*! \brief Extract a float from Any */
    float_x     to_float(const Any&);

    /*! \brief Extract an integer from Any */
    integer_x   to_int(const Any&);

    /*! \brief Extract an 8-bit integer from Any */
    int8_x      to_int8(const Any&);
    
    /*! \brief Extract a 16-bit integer from Any */
    int16_x     to_int16(const Any&);

    /*! \brief Extract a 32-bit integer from Any */
    int32_x     to_int32(const Any&);

    /*! \brief Extract a 64-bit integer from Any */
    int64_x     to_int64(const Any&);

    /*! \brief Extract an integer from Any */
    integer_x   to_integer(const Any&);

    /*! \brief Extract a short from Any */
    short_x     to_short(const Any&);

    /*! \brief Extract a string from Any */
    string_x    to_string(const Any&);

    /*! \brief Extract an unsigned integer from Any */
    unsigned_x  to_uint(const Any&);

    /*! \brief Extract an 8-bit unsigned integer from Any */
    uint8_x     to_uint8(const Any&);

    /*! \brief Extract a 16-bit unsigned integer from Any */
    uint16_x    to_uint16(const Any&);

    /*! \brief Extract a 32-bit unsigned integer from Any */
    uint32_x    to_uint32(const Any&);

    /*! \brief Extract a 64-bit unsigned integer from Any */
    uint64_x    to_uint64(const Any&);

    /*! \brief Extract an unsigned integer from Any */
    unsigned_x  to_uinteger(const Any&);

    /*! \brief Extract an unsigned short from Any */
    ushort_x    to_ushort(const Any&);
}

