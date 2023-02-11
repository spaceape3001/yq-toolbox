////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <type_traits>

namespace yq {
    //! Structure that is always true regardless of the template arguments
    template <typename...> struct always_true : std::true_type {};
    //! Boolean that is always true regardless of the template arguments
    template <typename...> static constexpr bool always_true_v    = true;
}
