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

    /*! \brief Extract a boolean from Any */
    boolean_r   to_boolean(const Any&);

    /*! \brief Extract a double from Any */
    double_r    to_double(const Any&);

    /*! \brief Extract a float from Any */
    float_r     to_float(const Any&);

    /*! \brief Extract an integer from Any */
    int_r       to_int(const Any&);

    /*! \brief Extract an 8-bit integer from Any */
    int8_r      to_int8(const Any&);
    
    /*! \brief Extract a 16-bit integer from Any */
    int16_r     to_int16(const Any&);

    /*! \brief Extract a 32-bit integer from Any */
    int32_r     to_int32(const Any&);

    /*! \brief Extract a 64-bit integer from Any */
    int64_r     to_int64(const Any&);

    /*! \brief Extract an integer from Any */
    integer_r   to_integer(const Any&);

    /*! \brief Extract a short from Any */
    short_r     to_short(const Any&);

    /*! \brief Extract a string from Any */
    string_r    to_string(const Any&);

    /*! \brief Extract an 8-bit unsigned integer from Any */
    uint8_r     to_uint8(const Any&);

    /*! \brief Extract a 16-bit unsigned integer from Any */
    uint16_r    to_uint16(const Any&);

    /*! \brief Extract a 32-bit unsigned integer from Any */
    uint32_r    to_uint32(const Any&);

    /*! \brief Extract a 64-bit unsigned integer from Any */
    uint64_r    to_uint64(const Any&);

    /*! \brief Extract an unsigned integer from Any */
    unsigned_r  to_uinteger(const Any&);

    /*! \brief Extract an unsigned short from Any */
    ushort_r    to_ushort(const Any&);
}

