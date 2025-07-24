////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <type_traits>

namespace yq {
    template <typename T> struct view_type : std::false_type {
        using type  = void;
    };
    
    
    template <typename T>  static constexpr bool view_type_v    = view_type<T>::value;
    template <typename T>  static constexpr bool has_view_type  = view_type<T>::value;
    template <typename T>  using view_type_t                    = view_type<T>::type;
}

#define YQ_VIEW_TYPE(cls, view)            \
template <>                             \
struct view_type<cls> : std::true_type {     \
    using type = view;                  \
};
