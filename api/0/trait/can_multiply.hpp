////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/trait/sink.hpp>

namespace yq {
    template <typename T> auto generic_multiply(const T& a, const T& b) { return a*b; }

    /*! \brief Trait to test for multiplication
    
        This trait will be TRUE if the type can multiply with itself.
    */
    template <typename T, typename=void> struct can_multiply : public std::false_type {};
    template <typename T> struct can_multiply<T,sink_t<decltype(T()*T())>> : public std::true_type {};
    //! \brief BOOLEAN to test if a type can multiply with itself
    template <typename T> static constexpr const bool can_multiply_v = can_multiply<T>::value;
}
