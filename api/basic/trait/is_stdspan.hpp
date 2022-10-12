////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <type_traits>
#include <span>

namespace yq {
    namespace trait {

        //! Tests for whetner a type is a standard span
        template <typename> struct is_stdspan : std::false_type {};
        template <typename T, std::size_t X>
        struct is_stdspan<std::span<T,X>> : std::true_type {};
        
        //! TRUE if type T is a std::span.
        template <typename T>
        inline constexpr bool is_stdspan_v = is_stdspan<T>::value;

    }
}
