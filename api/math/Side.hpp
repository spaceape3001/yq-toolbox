////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_SIDE_HPP 1

#include <cstdint>

namespace yq {
    
    //! Simple side flag-like object
    //!
    //! This is needed given we want to do more than is available for a simple flags object
    struct Side {
        // Mind-boggling how this gets defined...we're undoing that!
        #ifdef ERROR
        #undef ERROR
        #endif
        
        //! Our data
        uint8_t bits;
        
        enum : uint8_t {
            //! Error condition detected (ie, violation of lo <= hi)
            ERROR       = 1 << 0,
            
            //! Unable to compare (ie unknown)
            UNKNOWN     = 1 << 1,
            
            //! Coplanar
            COPLANER    = 1 << 2,
            
            //! Below the low limit
            BELOW       = 1 << 3,
            
            //! ON the low limit
            LOW         = 1 << 4,
            //! Between the two limits
            MIDDLE      = 1 << 5,
            //! ON the upper limit
            HIGH        = 1 << 6,
            
            //! Above the upper limit
            ABOVE       = 1 << 7,
            
            FAIL        = ERROR|UNKNOWN
        };

        //! Default constructor
        consteval Side() noexcept : bits(0) {}
        
        //! Constructs from single value
        constexpr Side(uint8_t b) noexcept : bits(b) {}
        
        //! Constructs from two values
        constexpr Side(uint8_t a, uint8_t b) noexcept : bits(a|b) {}
        
        //! Constructs from an initializer list
        constexpr Side(std::initializer_list<uint8_t> bs) noexcept : bits(0)
        {
            for(uint8_t u : bs)
                bits |= u;
        }
        
        //! TRUE if this side is a "fail"
        constexpr bool    is_fail() const { return bits & FAIL; }
        
        //! Defaulted comparison operator
        constexpr bool operator==(const Side&) const noexcept = default;
        
        //! And-operator of two sides
        constexpr Side operator&(Side b) const noexcept
        {
            return bits & b.bits;
        }
        
        
        //! Self-and of two sides
        Side& operator&=(Side b) noexcept
        {
            bits &= b.bits;
            return *this;
        }

        //! Or-operator of two sides
        constexpr Side operator|(Side b) const noexcept
        {
            return bits | b.bits;
        }

        //! Self-or operator of two sides
        Side& operator|=(Side b) noexcept
        {
            bits |= b.bits;
            return *this;
        }
        
        //! Bit inversion
        constexpr Side operator~() const  noexcept
        {
            return { !bits };
        }
    };
}
