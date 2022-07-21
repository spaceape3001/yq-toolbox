////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "sink.hpp"

namespace yq {
    namespace trait {
        template <typename T, typename=void> struct has_equality : public std::false_type {};
        template <typename T> struct has_equality<T, sink_t<decltype(T()==T())>> : public std::true_type {};
        template <typename T> static constexpr const bool has_equality_v = has_equality<T>::value;
    }
}
