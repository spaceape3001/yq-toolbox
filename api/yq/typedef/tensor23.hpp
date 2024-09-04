////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    template <typename> struct Tensor23;

    using Tensor23D                 = Tensor23<double>;
    using Tensor23F                 = Tensor23<float>;
    using Tensor23I                 = Tensor23<int>;
    using Tensor23U                 = Tensor23<unsigned>;
}
