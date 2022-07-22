////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    namespace trait {

        template <typename> struct is_template : std::false_type {};
        template <template <typename...> class Tmpl, typename ...Args>
        struct is_template<Tmpl<Args...>> : std::true_type {};
        
        template <typename T>
        inline constexpr bool is_template_v = is_template<T>::value;
    }
}
