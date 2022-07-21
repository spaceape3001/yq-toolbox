////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "sink.hpp"

namespace yq {
    namespace trait {
        template <typename T, typename=void> struct has_inequality : public std::false_type {};
        template <typename T> struct has_inequality<T, sink_t<decltype(T()!=T())>> : public std::true_type {};
        template <typename T> static constexpr const bool has_inequality_v = has_inequality<T>::value;
    }
}
