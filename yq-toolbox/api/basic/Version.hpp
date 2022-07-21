#pragma once

#include <cstdint>

namespace yq {
    struct Version {
        uint16_t    major   = 0;
        uint16_t    minor   = 0;
        uint16_t    patch   = 0;
        uint16_t    build   = 0;
        
        auto operator<=>(const Version&) const = default;
    };
}
