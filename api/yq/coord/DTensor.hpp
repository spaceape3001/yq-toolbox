////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {

    /*! \brief Domain based tensor value
    
        \tparam D   domain
        \tparam V   tensor type
    */
    template <class D, class V>
    struct DTensor : public V {
        constexpr DTensor() : V{} {}

        template <typename ... A>
        explicit DTensor(A... args) : V(args...) {}
    };
}
