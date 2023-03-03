////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/preamble.hpp>
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

            operator std::unexpected<std::error_code>() const
            {
                return std::unexpected<std::error_code>(*this);
            }

            template <typename T>
            operator std::expected<T, std::error_code>() const
            {
                return std::expected<T, std::error_code>(std::unexpect_t(), *this);
            }
        };

    }
}
