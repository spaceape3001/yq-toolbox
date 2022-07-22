////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>

namespace yq {
    namespace earth {
        //! 24-hour time-of-day
        struct Time {
            uint8_t hour    = 0;    // 0...23
            uint8_t minute  = 0;    // 0...59
            uint8_t second  = 0;    // 0...60 (for leap second)
            uint8_t percent = 0;    // 0...99
        };
        
    }
}
