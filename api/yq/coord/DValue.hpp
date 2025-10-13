////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {

    /*! \brief Domain based generic value (ie in ECEF system or the like)
        \tparam D   domain
        \tparam V   value (vector, unit, color, etc)
    */
    template <class D, class V>
    struct DValue : public V {
    
        constexpr DValue() : V{} {}

        template <typename ... A>
        explicit DValue(A... args) : V(args...) {}
    };

}
