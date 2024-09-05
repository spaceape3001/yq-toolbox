////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/trait/product.hpp>
#include <type_traits>

namespace yq {
    template <typename T, typename U>  using self_multiply                      = std::is_same<T,product_t<T,U>>;
    template <typename T, typename U>  static constexpr bool self_multiply_v    = self_divide<T,U>::value;
}
