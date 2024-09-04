////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    template <typename> struct Tensor41;

    using Tensor41D                 = Tensor41<double>;
    using Tensor41F                 = Tensor41<float>;
    using Tensor41I                 = Tensor41<int>;
    using Tensor41U                 = Tensor41<unsigned>;
}
