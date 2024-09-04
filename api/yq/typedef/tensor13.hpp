////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    template <typename> struct Tensor13;

    using Tensor13D                 = Tensor13<double>;
    using Tensor13F                 = Tensor13<float>;
    using Tensor13I                 = Tensor13<int>;
    using Tensor13U                 = Tensor13<unsigned>;
}
