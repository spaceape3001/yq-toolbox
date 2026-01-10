#pragma once

#include <cstdint>

namespace yq {
    
    //! Simple version structure (major/minor/patch/build)
    //! Uses 16-bit unsigned shorts to stay at 64-bits total
    struct Version {
    
        //! Major version number
        uint16_t    major   = 0;
        
        //! Minor version number
        uint16_t    minor   = 0;
        
        //! Patch version number
        uint16_t    patch   = 0;
        
        //! Build number
        uint16_t    build   = 0;
        
        auto operator<=>(const Version&) const = default;
    };
}
