////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    //! Auxillary data for coordinates (one in x, one in y, one in z)
    template <typename T>
    struct Vector3Data {
        //! Component type (captures the argument)
        using component_type    = T;

        T   x, y, z;

        //! Equality operator
        constexpr bool operator==(const Vector3Data&) const noexcept = default;
    };
}
