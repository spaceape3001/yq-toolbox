////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    template <typename> struct Tensor21;

    using Tensor21D                 = Tensor21<double>;
    using Tensor21F                 = Tensor21<float>;
    using Tensor21I                 = Tensor21<int>;
    using Tensor21U                 = Tensor21<unsigned>;
}
