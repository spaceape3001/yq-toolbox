////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/Vector2.hpp>
#include <math/Size2.hpp>

namespace yq {
    template <typename T>
    struct Rectangle2 {
        //! Component data type argument to this structure (ie, template parameter T)
        using component_type = T;

        Vector2<T>      position;
        Size2<T>        size;
        
        constexpr bool    operator==(const Rectangle2&) const noexcept = default;
    };

    YQ_IEEE754_1(Rectangle2)
    YQ_NAN_1(Rectangle2, Rectangle2<T>{nan_v<Vector2<T>>, nan_v<Size2<T>>})
    YQ_ZERO_1(Rectangle2, Rectangle2<T>{zero_v<Vector2<T>>, zero_v<Size2<T>>})
    

    YQ_IS_NAN_1(Rectangle2, is_nan(v.position) || is_nan(v.size))
    YQ_IS_FINITE_1(Rectangle2, is_finite(v.position) && is_finite(v.size))
}

YQ_TYPE_DECLARE(yq::Rectangle2D)
YQ_TYPE_DECLARE(yq::Rectangle2F)
YQ_TYPE_DECLARE(yq::Rectangle2I)
YQ_TYPE_DECLARE(yq::Rectangle2U)
