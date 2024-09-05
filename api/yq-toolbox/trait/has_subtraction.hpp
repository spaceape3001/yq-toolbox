////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/trait/sink.hpp>

namespace yq {
    //! Tests for subtraction operator on type
    template <typename T, typename=void> struct has_subtraction : public std::false_type {};
    template <typename T> struct has_subtraction<T, sink_t<decltype(T()-T())>> : public std::true_type {};
    //! TRUE if a type can be subtracted with itself
    template <typename T> static constexpr const bool has_subtraction_v = has_subtraction<T>::value;
}
