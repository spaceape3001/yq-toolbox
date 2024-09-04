////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    template <typename> struct Tensor12;

    using Tensor12D                 = Tensor12<double>;
    using Tensor12F                 = Tensor12<float>;
    using Tensor12I                 = Tensor12<int>;
    using Tensor12U                 = Tensor12<unsigned>;
}
