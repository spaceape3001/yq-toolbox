////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <system_error>
#include <basic/StringLiteral.hpp>

namespace yq {

    namespace error_db {
        const std::error_category&  category();
        //! REGISTERS a new reason
        //! \note Mutex is involved!
        int                         reason(const char*);

        template <StringLiteral WHY>
        struct entry : public std::error_code {
            static int      value() 
            {
                static int  c   = error_db::reason(WHY.value);
                return c;
            }
            
            entry() : std::error_code(value(), error_db::category()) {}
        };

    }
}
