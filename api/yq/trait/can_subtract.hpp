////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/trait/sink.hpp>

namespace yq {
    template <typename T> auto generic_subtract(const T& a, const T& b) { return a-b; }
    /*! \brief Trait to test for subtraction
    
        This trait will be TRUE if the type can subtract with itself.
    */
    template <typename T, typename=void> struct can_subtract : public std::false_type {};
    template <typename T> struct can_subtract<T,sink_t<decltype(T()-T())>> : public std::true_type {};
    //! \brief BOOLEAN to test if a type can subtract with itself
    template <typename T> static constexpr const bool can_subtract_v = can_subtract<T>::value;
}
