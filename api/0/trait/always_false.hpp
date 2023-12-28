////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <type_traits>

namespace yq {
    //! Structure that is always false regardless of the template arguments
    template <typename...> struct always_false : std::false_type {};
    //! Boolean that is always false regardless of the template arguments
    template <typename...> static constexpr bool always_false_v    = false;
}
