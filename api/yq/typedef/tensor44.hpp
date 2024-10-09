////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    template <typename> struct Tensor44;

    using Tensor44D                 = Tensor44<double>;
    using Tensor44F                 = Tensor44<float>;
    using Tensor44I                 = Tensor44<int>;
    using Tensor44U                 = Tensor44<unsigned>;
}
