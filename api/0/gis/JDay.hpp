////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/gis/preamble.hpp>
#include <yq-toolbox/meta/InfoBinder.hpp>

namespace yq {
    //! Julian day
    struct JDay {
        int32_t     jday    = 0;
        
        constexpr JDay() noexcept = default;
        constexpr JDay(int32_t j) noexcept : jday(j) {}
        
        static consteval JDay    gregorian();
        
        consteval JDay(gregorian_t);
        
        constexpr auto operator<=>(const JDay&) const noexcept = default;
        
        bool        is_gregorian() const;
    };

    consteval JDay::JDay(gregorian_t) : jday(2299161) // 15 Oct 1582
    {
    }
    
    JDay    jday(Date);
    JDay    jday(gregorian_t, Date);
    JDay    jday(julian_t, Date);
    JDay    jday(Calendar, Date);
    
}

YQ_TYPE_DECLARE(yq::JDay)
