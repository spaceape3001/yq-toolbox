////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/meta/AnyDef.hpp>
#include <0/meta/InfoBinder.hpp>
#include <0/meta/TypeInfo.hpp>
#include <0/meta/AnyImpl.hpp>

namespace yq {

    /*! \brief Extract a boolean from Any */
    Expect<bool>        to_boolean(const Any&);

    /*! \brief Extract a double from Any */
    Expect<double>      to_double(const Any&);

    /*! \brief Extract a float from Any */
    Expect<float>       to_float(const Any&);

    /*! \brief Extract an integer from Any */
    Expect<int>         to_int(const Any&);

    /*! \brief Extract an 8-bit integer from Any */
    Expect<int8_t>      to_int8(const Any&);
    
    /*! \brief Extract a 16-bit integer from Any */
    Expect<int16_t>     to_int16(const Any&);

    /*! \brief Extract a 32-bit integer from Any */
    Expect<int32_t>     to_int32(const Any&);

    /*! \brief Extract a 64-bit integer from Any */
    Expect<int64_t>     to_int64(const Any&);

    /*! \brief Extract an integer from Any */
    Expect<int>         to_integer(const Any&);

    /*! \brief Extract a short from Any */
    Expect<short>       to_short(const Any&);

    /*! \brief Extract a string from Any */
    Expect<std::string> to_string(const Any&);

    /*! \brief Extract an unsigned integer from Any */
    Expect<unsigned int> to_uint(const Any&);

    /*! \brief Extract an 8-bit unsigned integer from Any */
    Expect<uint8_t>     to_uint8(const Any&);

    /*! \brief Extract a 16-bit unsigned integer from Any */
    Expect<uint16_t>    to_uint16(const Any&);

    /*! \brief Extract a 32-bit unsigned integer from Any */
    Expect<uint32_t>    to_uint32(const Any&);

    /*! \brief Extract a 64-bit unsigned integer from Any */
    Expect<uint64_t>    to_uint64(const Any&);

    /*! \brief Extract an unsigned integer from Any */
    Expect<unsigned int> to_uinteger(const Any&);

    /*! \brief Extract an unsigned short from Any */
    Expect<unsigned short> to_ushort(const Any&);
}

