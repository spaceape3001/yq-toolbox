////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/trait/sink.hpp>

namespace yq {
    template <typename T> auto generic_divide(const T& a, const T& b) { return a/b; }

    /*! \brief Trait to test for division
    
        This trait will be TRUE if the type can divide with itself.
    */
    template <typename T, typename=void> struct can_divide : public std::false_type {};
    template <typename T> struct can_divide<T,sink_t<decltype(T()/T())>> : public std::true_type {};
    //! \brief BOOLEAN to test if a type can divide with itself
    template <typename T> static constexpr const bool can_divide_v = can_divide<T>::value;
}
