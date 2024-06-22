////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/trait/sink.hpp>

namespace yq {
    template <typename T, typename U> auto generic_two_divide(T a, U b) { return a/b; }

    /*! \brief Tests for two items being dividable
    
        This tests if a type T() can be divided by U()
        
        \tparam[T]  Dividend type
        \tparam[U]  Divisor type
    */
    template <typename T, typename U, typename=void> struct can_two_divide : public std::false_type {};
    template <typename T, typename U> struct can_two_divide<T,U,sink_t<decltype(T()/U())>> : public std::true_type {};
    
    /*! \brief Boolean flag for two items being dividable
        \tparam[T]  Dividend type
        \tparam[U]  Divisor type
    */
    template <typename T, typename U> static constexpr const bool can_two_divide_v = can_two_divide<T,U>::value;
}
