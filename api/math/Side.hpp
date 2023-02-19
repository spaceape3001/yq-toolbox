////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <cstdint>

namespace yq {
    
    struct Side {
        // Mind-boggling how this gets defined...we're undoing that!
        #ifdef ERROR
        #undef ERROR
        #endif
        
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

        consteval Side() noexcept : bits(0) {}
        constexpr Side(uint8_t b) noexcept : bits(b) {}
        constexpr Side(uint8_t a, uint8_t b) noexcept : bits(a|b) {}
        constexpr Side(std::initializer_list<uint8_t> bs) noexcept : bits(0)
        {
            for(uint8_t u : bs)
                bits |= u;
        }
        constexpr bool    is_fail() const { return bits & FAIL; }
        
        constexpr bool operator==(const Side&) const noexcept = default;
        
        constexpr Side operator&(Side b) const noexcept
        {
            return bits & b.bits;
        }
        
        Side& operator&=(Side b) noexcept
        {
            bits &= b.bits;
            return *this;
        }

        constexpr Side operator|(Side b) const noexcept
        {
            return bits | b.bits;
        }

        Side& operator|=(Side b) noexcept
        {
            bits |= b.bits;
            return *this;
        }
    };
}
