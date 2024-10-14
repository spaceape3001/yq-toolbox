////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>

namespace yq {
    template <uint8_t, class> struct Pixels;
    
    template <class C> using Pixels1 = Pixels<1,C>;
    template <class C> using Pixels2 = Pixels<2,C>;
    template <class C> using Pixels3 = Pixels<3,C>;
    template <class C> using Pixels4 = Pixels<4,C>;
}
