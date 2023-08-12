////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gis/preamble.hpp>
#include <meta/InfoBinder.hpp>

namespace yq {
    //! Julian day
    struct JDay {
        int32_t     jday    = 0;
        
        constexpr JDay() noexcept = default;
        constexpr JDay(int32_t j) noexcept : jday(j) {}
        
        static consteval JDay    gregorian();
        
        JDay(Date);
        
        consteval JDay(gregorian_t);
        
        JDay(gregorian_t, Date);
        JDay(julian_t, Date);
        JDay(Calendar, Date);
        
        constexpr auto operator<=>(const JDay&) const noexcept = default;
        
        bool        is_gregorian() const;
    };

    consteval JDay::JDay(gregorian_t) : jday(2299161) // 15 Oct 1582
    {
    }
}

YQ_TYPE_DECLARE(yq::JDay)
