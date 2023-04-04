////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "sink.hpp"

namespace yq {
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
