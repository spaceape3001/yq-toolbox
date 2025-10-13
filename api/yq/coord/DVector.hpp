////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {

    /*! \brief Domain based vector value (ie in ECEF or similar)
        \tparam D   domain
        \tparam V   vector type (should be vector 1/2/3/4, or bi/tri/quad/multi)
    */
    template <class D, class V>
    struct DVector : public V {
        constexpr DVector() : V{} {}

        template <typename ... A>
        explicit DVector(A... args) : V(args...) {}
    };
}
