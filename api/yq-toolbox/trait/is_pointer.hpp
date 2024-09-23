////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <type_traits>

namespace yq {

    template <typename> class Ref;
    
    template <typename T> struct is_pointer : std::is_pointer<T> {};
    template <typename T> struct is_pointer<Ref<T>> : std::true_type {};

    template <typename T>
    static constexpr bool is_pointer_v = is_pointer<T>::value;
    
    template <typename T>
    struct remove_pointer : std::remove_pointer<T> {};
    
    template <typename T>
    struct remove_pointer<Ref<T>> {
        using type = T;
    };
    
    template <typename T>
    struct remove_pointer<const Ref<T>> {
        using type = T;
    };
    
    template <typename T>
    using remove_pointer_t = remove_pointer<T>::type;
}
