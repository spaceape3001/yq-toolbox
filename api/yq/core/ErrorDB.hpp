////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/StringLiteral.hpp>
#include <yq/core/Expect.hpp>

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
        
        std::error_code     make_error(const char*);
    }
    
    //! Super more efficient
    template <StringLiteral WHY>
    std::error_code create_error()
    {
        return error_db::entry<WHY>();
    }
    
    //! Okay for one time use... note 
    template <size_t N>
    std::error_code create_error(StringLiteral<N> why)
    {
        return error_db::make_error(why.value);
    }

    //! Okay for one time use... note 
    template <StringLiteral WHY>
    std::unexpected<std::error_code> unexpected()
    {
        return error_db::entry<WHY>();
    }
    
    inline std::unexpected<std::error_code> unexpected(std::error_code ec)
    {
        return std::unexpected(ec);
    }
}
