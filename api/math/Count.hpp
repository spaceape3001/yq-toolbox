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
    */
    template <typename T>
    struct Count {
        static constexpr const T    MIN  = std::numeric_limits<T>::min();
        static constexpr const T    MAX  = std::numeric_limits<T>::max();
    
        T   cnt   = T(0);
        
            //! Comparison spaceship operator
        constexpr auto  operator<=>(const Count&) const noexcept = default;
        
            //! Implicit cast operator
        constexpr operator T() const noexcept { return cnt; }
        
            //! Pre-fix Increment operator
        Count operator++() { return Count{ ++cnt }; }

            //! Post-fix Increment operator
        Count operator++(int)  { return Count{ cnt++ }; }

            //! Pre-fix Deccrement operator
        Count operator--() { return Count{ --cnt }; }

            //! Post-fix Deccrement operator
        Count operator--(int)  { return Count{ cnt-- }; }

        void    increment()
        {
            if(cnt < MAX)
                ++cnt;
        }
        
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
