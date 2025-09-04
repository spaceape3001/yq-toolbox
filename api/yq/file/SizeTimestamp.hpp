////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstddef>
#include <cstdint>

namespace yq {

    //! Size/timestamp for last file modifications
    struct SizeTimestamp {
    
        //! Size of the file (bytes)
        size_t          size   = 0;
        
        //! Time of the file's last modification (seconds of epoch)
        uint64_t        time   = 0;
        
        //! Nanosecons of the file's last modification (seconds of epoch)
        uint64_t        nano   = 0;
        
        //! TRUE if the file exists
        bool            exists = false;
        
        //! Default Constructor
        constexpr SizeTimestamp() : size{}, time{}, nano{}, exists(false) {}
        
        //! Piecewise constructor
        constexpr SizeTimestamp(size_t s, uint64_t t, uint64_t n) : size(s), time(t), nano(n), exists(true) {}

        //! Total number of nanoseconds from epoch
        constexpr uint64_t        nanoseconds() const noexcept { return 1'000'000'000*time + nano; }
        
        //! Equality operator (defaulted)
        bool    operator==(const SizeTimestamp&) const noexcept = default;
    };

}
