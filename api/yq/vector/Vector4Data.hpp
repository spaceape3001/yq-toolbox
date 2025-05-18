////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    //! Auxillary data for coordinates (one in x, one in y, one in z, one in w)
    template <typename T>
    struct Vector2Data {
        //! Component type (captures the argument)
        using component_type    = T;

        T   x, y, z, w;

        //! Equality operator
        constexpr bool operator==(const Vector4Data&) const noexcept = default;
    };
}
