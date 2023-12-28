////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/gis/preamble.hpp>
#include <span>
#include <0/meta/InfoBinder.hpp>

namespace yq {
    /*! \brief Hour Minute Second
    
    */
    struct Time {
        uint8_t hour    = 0;    // 0...23
        uint8_t minute  = 0;    // 0...59
        uint8_t second  = 0;    // 0...60 (for leap second)
        uint8_t percent = 0;    // 0...99
        
        constexpr bool operator==(const Time&) const noexcept = default;
    };

    //! Table of known leap seconds
    std::span<const Date>   leap_seconds();
}

YQ_TYPE_DECLARE(yq::Time)
