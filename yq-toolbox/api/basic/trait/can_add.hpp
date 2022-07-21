////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "sink.hpp"

namespace yq {
    namespace trait {
        template <typename T, typename=void> struct can_add : public std::false_type {};
        template <typename T> struct can_add<T,sink_t<decltype(T()+T())>> : public std::true_type {};
        template <typename T> static constexpr const bool can_add_v = can_add<T>::value;
    }
}
