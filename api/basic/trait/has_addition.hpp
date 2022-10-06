////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "sink.hpp"

namespace yq {
    namespace trait {
        //! Tests for addition on type
        //! This detects if a type T can be added together
        template <typename T, typename=void> struct has_addition : public std::false_type {};
        template <typename T> struct has_addition<T, sink_t<decltype(T()+T())>> : public std::true_type {};
        //! TRUE if the type T has addition capability
        template <typename T> static constexpr const bool has_addition_v = has_addition<T>::value;
    }
}
