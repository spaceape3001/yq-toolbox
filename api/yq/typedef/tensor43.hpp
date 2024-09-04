////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    template <typename> struct Tensor43;

    using Tensor43D                 = Tensor43<double>;
    using Tensor43F                 = Tensor43<float>;
    using Tensor43I                 = Tensor43<int>;
    using Tensor43U                 = Tensor43<unsigned>;
}
