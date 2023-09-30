////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>

#include <cstdint>
#include <limits>

namespace yq {

        // QUASH these... if defined.
    #ifdef max
        #undef max
    #endif
    #ifdef MAX
        #undef MAX
    #endif
    #ifdef min
        #undef min
    #endif
    #ifdef MIN
        #undef MIN
    #endif

    /*! \brief Simple count that's always zero-initialized
    
        \tparam T   counter type
        \tparam R   value to reset to
    */
    template <typename T, T R>
    struct Counter {
    
            //! Min value ever
        static constexpr const T    MIN  = std::numeric_limits<T>::min();
        
            //! Max value ever
        static constexpr const T    MAX  = std::numeric_limits<T>::max();
    
            //! Our count
        T   cnt   = R;
        
            //! Comparison spaceship operator
        constexpr auto  operator<=>(const Counter&) const noexcept = default;
        
            //! Implicit cast operator
        constexpr operator T() const noexcept { return cnt; }
        
            //! Pre-fix Increment operator
        Counter operator++() { return Counter{ ++cnt }; }

            //! Post-fix Increment operator
        Counter operator++(int)  { return Counter{ cnt++ }; }

            //! Pre-fix Deccrement operator
        Counter operator--() { return Counter{ --cnt }; }

            //! Post-fix Deccrement operator
        Counter operator--(int)  { return Counter{ cnt-- }; }
        
            //! sets to the smaller
        void    set_smaller(Counter r)
        {
            if(r.cnt<cnt)
                cnt = r.cnt;
        }
        
            //! Sets to the biggger
        void    set_bigger(Counter r)
        {
            if(r.cnt>cnt)
                cnt = r.cnt;
        }

            //! Increments but stops at max value
        void    increment()
        {
            if(cnt < MAX)
                ++cnt;
        }
        
            //! Decrements but stops at min value
        void    decrement()
        {
            if(cnt > MIN)
                --cnt;
        }
       
    };
}

YQ_TYPE_DECLARE(yq::CountI8)
YQ_TYPE_DECLARE(yq::CountI16)
YQ_TYPE_DECLARE(yq::CountI32)
YQ_TYPE_DECLARE(yq::CountI64)

YQ_TYPE_DECLARE(yq::CountU8)
YQ_TYPE_DECLARE(yq::CountU16)
YQ_TYPE_DECLARE(yq::CountU32)
YQ_TYPE_DECLARE(yq::CountU64)

YQ_TYPE_DECLARE(yq::HCountI8)
YQ_TYPE_DECLARE(yq::HCountI16)
YQ_TYPE_DECLARE(yq::HCountI32)
YQ_TYPE_DECLARE(yq::HCountI64)

YQ_TYPE_DECLARE(yq::HCountU8)
YQ_TYPE_DECLARE(yq::HCountU16)
YQ_TYPE_DECLARE(yq::HCountU32)
YQ_TYPE_DECLARE(yq::HCountU64)

YQ_TYPE_DECLARE(yq::LCountI8)
YQ_TYPE_DECLARE(yq::LCountI16)
YQ_TYPE_DECLARE(yq::LCountI32)
YQ_TYPE_DECLARE(yq::LCountI64)
