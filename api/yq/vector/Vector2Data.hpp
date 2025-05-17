////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    //! Auxillary data for coordinates (one in x, one in y)
    template <typename T>
    struct Vector2Data {
        //! Component type (captures the argument)
        using component_type    = T;

        T   x, y;
        //! Equality operator
        constexpr bool operator==(const Vector2Data&) const noexcept = default;
    };
}
