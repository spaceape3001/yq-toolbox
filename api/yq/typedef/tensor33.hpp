////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    template <typename> struct Tensor33;

    using Tensor33D                 = Tensor33<double>;
    using Tensor33F                 = Tensor33<float>;
    using Tensor33I                 = Tensor33<int>;
    using Tensor33U                 = Tensor33<unsigned>;
}
