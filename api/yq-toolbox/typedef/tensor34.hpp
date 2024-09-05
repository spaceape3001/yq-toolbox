////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    template <typename> struct Tensor34;

    using Tensor34D                 = Tensor34<double>;
    using Tensor34F                 = Tensor34<float>;
    using Tensor34I                 = Tensor34<int>;
    using Tensor34U                 = Tensor34<unsigned>;
}
