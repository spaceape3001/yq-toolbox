////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "sink.hpp"

namespace yq {
    namespace trait {
        template <typename T, typename U, typename=void> struct can_two_divide : public std::false_type {};
        template <typename T, typename U> struct can_two_divide<T,U,sink_t<decltype(T()/U())>> : public std::true_type {};
        template <typename T, typename U> static constexpr const bool can_two_divide_v = can_two_divide<T,U>::value;
    }
}
