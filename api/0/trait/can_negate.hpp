////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/trait/sink.hpp>

namespace yq {
    template <typename T> auto generic_negate(const T& a) { return -a; }

    /*! \brief Trait to test for negation
    
        This trait will be TRUE if the type can be negated.
    */
    template <typename T, typename=void> struct can_negate : public std::false_type {};
    template <typename T> struct can_negate<T,sink_t<decltype(-T())>> : public std::true_type {};
    //! \brief BOOLEAN to test if a type can negate with itself
    template <typename T> static constexpr const bool can_negate_v = can_negate<T>::value;
}
