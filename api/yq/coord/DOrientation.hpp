////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    /*! \brief Domain based orientation value
    
        \tparam D   domain
        \tparam V   orientation type (ie, quaternion, spinor, angle)
    */
    template <class D, class V>
    struct DOrientation : public V {
    
        constexpr DOrientation() : V{} {}

        template <typename ... A>
        explicit DOrientation(A... args) : V(args...) {}

    };
}
