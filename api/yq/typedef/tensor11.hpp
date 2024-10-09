////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    template <typename> struct Tensor11;

    using Tensor11D                 = Tensor11<double>;
    using Tensor11F                 = Tensor11<float>;
    using Tensor11I                 = Tensor11<int>;
    using Tensor11U                 = Tensor11<unsigned>;
}
