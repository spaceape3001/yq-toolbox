////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    /*! \brief Domain based quaternion value
    
        \tparam D   domain
        \tparam V   Quaternion type
    */
    template <class D, class V>
    struct DQuaternion : public V {
        constexpr DValue() : V{} {}

        template <typename ... A>
        explicit DValue(A... args) : V(args...) {}
    };
}
