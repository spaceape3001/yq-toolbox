////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    // Two dimensional representation of a scan along a line of constant X
    template <typename I>
    struct ScanLine2X {
        I  x  = {};
        I  y0 = {};
        I  y1 = {};
    };

    // Two dimensional representation of a scan along a line of constant Y
    template <typename I>
    struct ScanLine2Y {
        I  x0 = {};
        I  x1 = {};
        I  y  = {};
    };
}
