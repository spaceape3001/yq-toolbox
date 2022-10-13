////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <type_traits>
#include <vector>

namespace yq {
    namespace trait {

        //! Tests a type to see if it's a std::vector
        template <typename> struct is_stdvector : std::false_type {};
        template <typename T, typename A>
        struct is_stdvector<std::vector<T,A>> : std::true_type {};
        
        //! TRUE if a type is std::vector
        template <typename T>
        inline constexpr bool is_stdvector_v = is_stdvector<T>::value;

    }
}
