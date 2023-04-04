////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "sink.hpp"

namespace yq {

    //! Tests for presents of equality on a type
    template <typename T, typename=void> struct has_equality : public std::false_type {};
    template <typename T> struct has_equality<T, sink_t<decltype(T()==T())>> : public std::true_type {};
    
    //! TRUE if the type has an equality operator defined for it.
    template <typename T> static constexpr const bool has_equality_v = has_equality<T>::value;
}
