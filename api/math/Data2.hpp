////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_DATA2_HPP 1

namespace yq {

    /*! \brief Simple structure for 2-dimensional data

        No math, simple data storage.
    */
    template <typename T>
    struct Data2 {
        T   x, y;
        constexpr bool operator==(const Data2&) const noexcept = default;
    };
}
