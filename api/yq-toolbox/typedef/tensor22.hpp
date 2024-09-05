////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    template <typename> struct Tensor22;

    using Tensor22D                 = Tensor22<double>;
    using Tensor22F                 = Tensor22<float>;
    using Tensor22I                 = Tensor22<int>;
    using Tensor22U                 = Tensor22<unsigned>;
}
