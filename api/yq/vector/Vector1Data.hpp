////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    //! Auxillary data for coordinates (one in x)
    template <typename T>
    struct Vector1Data {
        //! Component type (captures the argument)
        using component_type    = T;

        T   x;

        //! Equality operator
        constexpr bool operator==(const Vector1Data&) const noexcept = default;
    };
}
