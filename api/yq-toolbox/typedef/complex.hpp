////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace std {
    template <typename> class complex;
}

namespace yq {
    using ComplexD = std::complex<double>;
    using ComplexF = std::complex<float>;
    using ComplexI = std::complex<int>;
    using ComplexU = std::complex<unsigned>;
}
