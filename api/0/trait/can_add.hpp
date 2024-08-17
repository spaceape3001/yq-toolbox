////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/trait/sink.hpp>

namespace yq {
    template <typename T> auto generic_add(const T& a, const T& b) { return a+b; }

    /*! \brief Trait to test for addition
    
        This trait will be TRUE if the type can add with itself.
    */
    template <typename T, typename=void> struct can_add : public std::false_type {};
    template <typename T> struct can_add<T,sink_t<decltype(T()+T())>> : public std::true_type {};
    //! \brief BOOLEAN to test if a type can add with itself
    template <typename T> static constexpr const bool can_add_v = can_add<T>::value;
}
