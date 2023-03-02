////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_DATA3_HPP 1

namespace yq {

    /*! \brief Simple structure for 3-dimensional data

        No math, simple data storage.
    */
    template <typename T>
    struct Data3 {
        T   x, y, z;
        constexpr bool operator==(const Data3&) const noexcept = default;
    };
}
