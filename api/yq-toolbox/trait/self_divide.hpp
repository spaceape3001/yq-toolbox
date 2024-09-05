////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/trait/quotient.hpp>
#include <type_traits>

namespace yq {
    template <typename T, typename U>  using self_divide                        = std::is_same<T,quotient_t<T,U>>;
    template <typename T, typename U>  static constexpr bool self_divide_v      = self_divide<T,U>::value;
}
