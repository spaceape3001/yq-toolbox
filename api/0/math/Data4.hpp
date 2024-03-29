////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_DATA4_HPP 1

namespace yq {

    /*! \brief Simple structure for 4-dimensional data

        No math, simple data storage.
    */
    template <typename T>
    struct Data4 {

        //! Data in the x-axis
        T   x;
        
        //! Data in the y-axis
        T   y;
        
        //! Data in the z-axis
        T   z;

        //! Data in the w-axis
        T   w;
        
        //! Equality operator (defaulted)
        constexpr bool operator==(const Data4&) const noexcept = default;
    };
}
