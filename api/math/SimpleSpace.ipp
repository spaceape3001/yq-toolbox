////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SimpleSpace.hpp"
#include <math/tensor_math.hpp>

namespace yq {
    Tensor44D       SimpleSpace::local2parent() const
    {
        Tensor33D   T   = tensor(orientation) * diagonal(scale);
        return {
            T.xx, T.xy, T.xz, position.x,
            T.yx, T.yy, T.yz, position.y,
            T.zx, T.zy, T.zz, position.z,
            0., 0., 0., 1.
        };
    }

    Tensor44D       SimpleSpace::parent2local() const
    {
        Tensor33    T   = diagonal(1./scale.x, 1./scale.y, 1./scale.z) * tensor(conjugate(orientation));
        Vector3D    pos = T * position;
        return {
            T.xx, T.xy, T.xz, -pos.x,
            T.yx, T.yy, T.yz, -pos.y,
            T.zx, T.zy, T.zz, -pos.z,
            0., 0., 0., 1.
        };
    }
}

