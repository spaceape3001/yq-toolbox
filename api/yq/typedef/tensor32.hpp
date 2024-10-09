////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    template <typename> struct Tensor32;

    using Tensor32D                 = Tensor32<double>;
    using Tensor32F                 = Tensor32<float>;
    using Tensor32I                 = Tensor32<int>;
    using Tensor32U                 = Tensor32<unsigned>;
}
