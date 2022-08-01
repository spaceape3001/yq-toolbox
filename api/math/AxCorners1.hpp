////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <math/preamble.hpp>

namespace yq {

    /*! \brief Store data for corners of 1D box
    */
    template <typename T>
    struct AxCorners1 {
        using component_type    = T;
    
        T   l;
        T   h;
        
        bool operator==(const AxCorners1&) const noexcept = default;
    };
}

