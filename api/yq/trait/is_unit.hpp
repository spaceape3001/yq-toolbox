////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <type_traits>

namespace yq {
    template <typename T, typename DIM>             struct MKS;
    template <typename T, typename DIM, double K>   struct SCALED;

    template <typename T> struct is_mks : std::false_type {};
    template <typename T, typename DIM> struct is_mks<MKS<T,DIM>> : std::true_type {};
    template <typename T> static constexpr const bool is_mks_v = is_mks<T>::value;
    
    template <typename T> struct is_scaled : std::false_type {};
    template <typename T, typename DIM, double K> struct is_scaled<SCALED<T,DIM,K>> : std::true_type {};
    template <typename T> static constexpr const bool is_scaled_v = is_scaled<T>::value;
    
    template <typename T> static constexpr const bool is_unit_v = is_mks_v<T> || is_scaled_v<T>;
}
