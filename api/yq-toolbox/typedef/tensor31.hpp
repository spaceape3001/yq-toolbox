////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    template <typename> struct Tensor31;

    using Tensor31D                 = Tensor31<double>;
    using Tensor31F                 = Tensor31<float>;
    using Tensor31I                 = Tensor31<int>;
    using Tensor31U                 = Tensor31<unsigned>;
}
