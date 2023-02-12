////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <system_error>
#include <basic/trait/string_literal.hpp>

namespace yq {

    namespace error_db {
        const std::error_category&  category();
        //! REGISTERS a new reason
        //! \note Mutex is involved!
        int                         reason(const char*);
    }

    template <string_literal WHY>
    struct error_code : public std::error_code {
        static int      value() 
        {
            static int  c   = error_db::reason(WHY.value);
            return c;
        }
        
        error_code() : std::error_code(value(), error_db::category()) {}
    };
}
