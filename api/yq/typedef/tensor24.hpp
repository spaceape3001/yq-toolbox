////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    template <typename> struct Tensor24;

    using Tensor24D                 = Tensor24<double>;
    using Tensor24F                 = Tensor24<float>;
    using Tensor24I                 = Tensor24<int>;
    using Tensor24U                 = Tensor24<unsigned>;
}
