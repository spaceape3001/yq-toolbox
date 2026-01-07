#pragma once

#include <cstdint>

namespace yq {
    
    //! Simple version structure (major/minor/patch/build)
    struct Version {
    
        //! Major version number
        uint16_t    major   = 0;
        uint16_t    minor   = 0;
        uint16_t    patch   = 0;
        uint16_t    build   = 0;
        
        auto operator<=>(const Version&) const = default;
    };
}
