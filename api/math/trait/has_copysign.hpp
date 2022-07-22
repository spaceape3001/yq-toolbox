////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <type_traits>
#include <cstdlib>
#include <cmath>

namespace yq {
    template <typename T, typename U>
    struct copysign_eval : std::false_type {
    };

    namespace trait {
        template <typename T, typename U=T> static constexpr const bool has_copysign_v = copysign_eval<T,U>::value;
    }
    
    template <typename T, typename U>
    requires trait::has_copysign_v<T,U>
    auto copysign(const T& mag, const U& sgn)
    {
        return copysign_eval<T,U>::compute(mag, sgn);
    }

    template <typename T, typename U>
    requires (std::is_floating_point_v<T> && std::is_floating_point_v<U> && std::is_convertible_v<U,T>)
    struct copysign_eval<T,U> : std::true_type { 
        static constexpr auto compute(T mag, U sgn) 
        {
            return std::copysign(mag, (T) sgn);
        }
    };


}
