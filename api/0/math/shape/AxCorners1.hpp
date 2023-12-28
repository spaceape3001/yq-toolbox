////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_AXCORNERS1_HPP 1

#include <0/math/preamble.hpp>

namespace yq {

    /*! \brief Store data for corners of 1D box
    */
    template <typename T>
    struct AxCorners1 {
    
        //! Component type (capturing the argument)
        using component_type    = T;
    
        //! Lower corner data
        T   l;
        
        //! Upper corner data
        T   h;
        
        //! Equality operator
        constexpr bool operator==(const AxCorners1&) const noexcept = default;
    };
}

