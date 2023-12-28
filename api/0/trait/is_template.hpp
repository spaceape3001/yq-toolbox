////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <type_traits>

namespace yq {

    //! Tests to see if type T is a template
    template <typename> struct is_template : std::false_type {};
    template <template <typename...> class Tmpl, typename ...Args>
    struct is_template<Tmpl<Args...>> : std::true_type {};
    
    //! TRUE if the given type is a template
    template <typename T>
    inline constexpr bool is_template_v = is_template<T>::value;
}
