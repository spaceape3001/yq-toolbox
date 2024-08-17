////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/trait/sink.hpp>

namespace yq {
    template <typename T, typename U> auto generic_two_subtract(const T& a, const U& b) { return a-b; }

    //! Tests for two types that can can add
    //! \tparam T   left term type
    //! \tparam U   right term type
    template <typename T, typename U, typename=void> struct can_two_subtract : public std::false_type {};
    template <typename T, typename U> struct can_two_subtract<T,U,sink_t<decltype(T()-U())>> : public std::true_type {};
    
    //! Boolean that's true if the two types can add
    //! \tparam T   left term type
    //! \tparam U   right term type
    template <typename T, typename U> static constexpr const bool can_two_subtract_v = can_two_subtract<T,U>::value;
}
