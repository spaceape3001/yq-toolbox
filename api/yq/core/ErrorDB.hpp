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
		
		//! Category for YQ Errors
        const std::error_category&  category();

        //! REGISTERS a new reason
        //! \note Mutex is involved!
        int                         reason(const char*);

		/*! Error code entry
			\tparam[WHY] The reason for the error
		*/
        template <StringLiteral WHY>
        struct entry : public std::error_code {
			//! Integer value for this error 
			//! \note Static/fixed to the message for the runtime duration
            static int      value() 
            {
                static int  c   = error_db::reason(WHY.value);
                return c;
            }
            
            //! Default constructor
            entry() : std::error_code(value(), error_db::category()) {}

			//! Implicit conversion to an unexpected
            operator std::unexpected<std::error_code>() const
            {
                return std::unexpected<std::error_code>(*this);
            }

			//! Implicit conversion to std expected
            template <typename T>
            operator std::expected<T, std::error_code>() const
            {
                return std::expected<T, std::error_code>(std::unexpect_t(), *this);
            }
        };
        
        /*! Makes an error code for the given reason
        */
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
