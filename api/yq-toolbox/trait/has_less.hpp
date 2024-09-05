////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/trait/sink.hpp>

namespace yq {
    //! Tests for the presence of "less-than" capability for a type
    template <typename T, typename=void> struct has_less : public std::false_type {};
    template <typename T> struct has_less<T, sink_t<decltype(T()<T())>> : public std::true_type {};
    //! TRUE if the type can be compared with a "less-than" operator
    template <typename T> static constexpr const bool has_less_v = has_less<T>::value;
}
