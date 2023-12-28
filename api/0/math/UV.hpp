////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/keywords.hpp>

namespace yq {
    /*! \brief UV coordinate type
        \tparam T   data type
    */
    template <typename T>
    struct UV {
    
        //! Data in u
        T   u;
        
        //! Data in v
        T   v;

        //! Default constructor
        constexpr UV() noexcept = default;
        
        //! Componentwise constructor
        constexpr UV(const T& _u, const T& _v) noexcept : u(_u), v(_v) {}
        
        //! Construct with all components to same value
        constexpr UV(all_t, const T& _val) noexcept : u(_val), v(_val) {}
        
        //! Defaulted equality operator
        constexpr bool operator==(const UV&) const noexcept = default;
    };
}

