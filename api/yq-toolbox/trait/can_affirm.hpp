////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/trait/sink.hpp>

namespace yq {
    template <typename T> auto generic_affirm(const T& a) { return +a; }
    /*! \brief Trait to test for negation
    
        This trait will be TRUE if the type can be affirmd.
    */
    template <typename T, typename=void> struct can_affirm : public std::false_type {};
    template <typename T> struct can_affirm<T,sink_t<decltype(+T())>> : public std::true_type {};
    //! \brief BOOLEAN to test if a type can affirm with itself
    template <typename T> static constexpr const bool can_affirm_v = can_affirm<T>::value;
}
