////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <utility>

namespace yq {

    /*! \brief General dual-return of value/created-flag
    
        Should be more descriptive than std::pair
    */
    template <typename T>
    struct Created {
		
		//! Value of the created object
        T       value;
        
        //! TRUE if the item was created by the call
        bool    created = false;
        
        //! Reference to the value, allows for passing to other functions
        operator const T& () const { return value; }
        
        //! Equality operator (defaulted)
        bool operator==(const Created&) const noexcept = default;
        
        template <typename U>
        Created<U>       cast_to() const
        {
            return Created<U>{(U) value, created};
        }
        
        constexpr operator std::pair<T,bool>() const { return std::pair<T,bool>(value, created); }
        
    };
}
