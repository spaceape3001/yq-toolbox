////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    template <typename, typename I=unsigned> struct Polymesh3;

    using Polymesh3D                = Polymesh3<double>;
    using Polymesh3F                = Polymesh3<float>;
    using Polymesh3I                = Polymesh3<int>;
    using Polymesh3U                = Polymesh3<unsigned>;
}
