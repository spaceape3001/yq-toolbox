////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    template <typename> struct Tensor42;

    using Tensor42D                 = Tensor42<double>;
    using Tensor42F                 = Tensor42<float>;
    using Tensor42I                 = Tensor42<int>;
    using Tensor42U                 = Tensor42<unsigned>;
}
