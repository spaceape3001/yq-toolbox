////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>

namespace yq {

    struct SizeTimestamp {
        size_t          size   = 0;
        uint64_t        time   = 0;
        uint64_t        nano   = 0;
        bool            exists = false;
        
        SizeTimestamp() : size{}, time{}, nano{}, exists(false) {}
        SizeTimestamp(size_t s, uint64_t t, uint64_t n) : size(s), time(t), nano(n), exists(true) {}
        uint64_t        nanoseconds() const { return 1'000'000'000*time + nano; }
        bool    operator==(const SizeTimestamp&) const = default;
    };

}
