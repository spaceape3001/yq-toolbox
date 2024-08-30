////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/trait/sink.hpp>

namespace yq {
    template <typename T, typename U> auto generic_two_add(const T& a, const U& b) { return a+b; }

    //! Test to see if two types can add
    template <typename T, typename U, typename=void> struct can_two_add : public std::false_type {};
    template <typename T, typename U> struct can_two_add<T,U,sink_t<decltype(T()+U())>> : public std::true_type {};
    //! Boolean to see if two types can add together
    template <typename T, typename U> static constexpr const bool can_two_add_v = can_two_add<T,U>::value;
}
