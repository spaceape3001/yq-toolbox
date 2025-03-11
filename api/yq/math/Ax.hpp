////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>

namespace yq {

    //! Axis code... this'll be shared on usage
    enum class Ax : uint8_t {
        None = 0,
        I,
        J,
        K,
        L,
        M,
        N,
        U,
        V,
        W,
        X,
        Y,
        Z,
        
        Ip = I,
        Jp = J,
        Kp = K,
        Lp = L,
        Mp = M,
        Np = N,
        
        Up = U,
        Vp = V,
        Wp = W,
        
        Xp = X,
        Yp = Y,
        Zp = Z,
        
        In,
        Jn,
        Kn,
        Ln,
        Mn,
        Nn,
        Un,
        Vn,
        Wn,
        Xn,
        Yn,
        Zn
    };
}
