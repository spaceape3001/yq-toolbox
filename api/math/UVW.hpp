////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <keywords.hpp>

namespace yq {

    /*! \brief UVW data structure
    
        Used to bind together uvw triple binding of data to the relevant axes
    */
    template <typename T>
    struct UVW {
    
        //! Data for the U-axis
        T   u;
        
        //! Data for the V-axis
        T   v;
        
        //! Data for the W-axis
        T   w;
        
        //! Default constructor
        constexpr UVW() noexcept = default;
        
        //! Component-wise constructor
        constexpr UVW(const T& _u, const T& _v, const T& _w) noexcept : u(_u), v(_v), w(_w) {}
        
        //! Constructs all data to same value
        constexpr UVW(all_t, const T& _val) noexcept : u(_val), v(_val), w(_val) {}
        
        //! Defaulted equality operator
        constexpr bool operator==(const UVW&) const noexcept = default;
    };
}

