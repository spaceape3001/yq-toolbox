////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>

namespace yq {
    struct Count16 {
        uint16_t        cnt = 0;
        constexpr operator uint16_t() const noexcept { return cnt; }
        constexpr auto operator<=>(const Count16&) const = default;
        
        Count16    operator++() noexcept
        {
            return { ++cnt };
        }
        Count16    operator++(int) noexcept
        {
            return { cnt++ };
        }
        Count16    operator--() noexcept
        {
            return { --cnt };
        }
        Count16    operator--(int) noexcept
        {
            return { cnt-- };
        }
            // safely increment (max out at 65k)
        void    increment()
        {
            if(cnt < UINT16_MAX)
                ++cnt;
        }
            // safely decrement (min count 0)
        void    decrement()
        {
            if(cnt)
                --cnt;
        }
    };
}
