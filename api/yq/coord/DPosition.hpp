////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    /*! \brief Domain based position value
    
        \tparam D   domain
        \tparam V   position type (vector/polar/etc)
    */
    template <class D, class V>
    struct DPosition : public V {
        constexpr DPosition() : V{} {}

        template <typename ... A>
        explicit DPosition(A... args) : V(args...) {}
    };
}
