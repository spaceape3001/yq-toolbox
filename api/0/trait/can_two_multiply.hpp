////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/trait/sink.hpp>

namespace yq {
    /*! \brief Trait for detecting two types can be multiplied together
    
        \tparam[T]  left hand side
        \tparam[U]  Right hand side
    */
    template <typename T, typename U, typename=void> struct can_two_multiply : public std::false_type {};
    template <typename T, typename U> struct can_two_multiply<T,U,sink_t<decltype(T()*U())>> : public std::true_type {};
    
    //! Boolean for detecting two types as being capable of being multiplied
    template <typename T, typename U> static constexpr const bool can_two_multiply_v = can_two_multiply<T,U>::value;
}
