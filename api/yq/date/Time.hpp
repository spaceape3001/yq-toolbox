////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/MetaBinder.hpp>
#include <span>

namespace log4cpp { class CategoryStream; }

namespace yq {
    struct Date;
    
    /*! \brief Hour Minute Second
    
        General purpose HMS.%% time structure, not for high-resolution purposes.
    */
    struct Time {
        uint8_t hour    = 0;    // 0...23
        uint8_t minute  = 0;    // 0...59
        uint8_t second  = 0;    // 0...60 (for leap second)
        uint8_t percent = 0;    // 0...99
        
        constexpr bool operator==(const Time&) const noexcept = default;
        
        static const std::span<const Date>    kLeapSeconds;
    };
}

YQ_TYPE_DECLARE(yq::Time)
