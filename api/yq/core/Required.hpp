////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>

namespace yq {
    /*! \brief Enumeration for required values
    
        Used when a tristate is needed for require-values
    */
    enum class Required : uint8_t {
        //! Feature not required/used
        NO = 0,
        //! Feature used, but not required
        OPTIONAL,
        //! Feature used and is required
        YES
    };
}

