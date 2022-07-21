////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "sink.hpp"

namespace yq {
    namespace trait {
        template <typename T, typename=void> struct has_less : public std::false_type {};
        template <typename T> struct has_less<T, sink_t<decltype(T()<T())>> : public std::true_type {};
        template <typename T> static constexpr const bool has_less_v = has_less<T>::value;
    }
}
