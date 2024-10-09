////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq { struct UInt128; }

#if defined(__GNUC__)

    //  Linux suppourts int128
    //! 128 bit unsigned integer (gcc native)
    using uint128_t = unsigned __int128;

    //! 128 bit signed integer (gcc native)
    using int128_t  = __int128;

#else
    #error "Need to specify 128-bit integers in compiler/architecture"
#endif
