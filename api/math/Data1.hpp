////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {

    /*! \brief Simple structure for 1-dimensional data

        No math, simple data storage.
    */
    template <typename T>
    struct Data1 {
        T   x;
        constexpr bool operator==(const Data1&) const noexcept = default;
    };
}
