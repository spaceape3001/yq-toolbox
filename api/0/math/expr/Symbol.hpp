////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <string_view>
#include <0/basic/Enum.hpp>
#include <functional>
#include <0/basic/preamble.hpp>
#include <0/math/expr/preamble.hpp>
#include <iosfwd>

namespace log4cpp { class CategoryStream; }

namespace yq::expr {
    /*! \brief Symbol Type
    
        Used at various stages
    */
    YQ_ENUM(SymType,,
        //! Not a symbol
        None    = 0,
        
            //  THESE come off the base parser

        //! An error occured
        Error,

        //! White space
        Space,

        //! Operator
        Operator,
        
        //! Text (variable, constant, function, etc)
        Text,
        
        //! Hexadecimal constant
        Hex,
        
        //! Octal constant
        Octal,
        
        //! Integer constant
        Int,
        
        //! Floating point constant
        Float,
        
            // THESE are subsequently interpretted from the above
        
        //! Variable being referred to
        Variable,
        
        //! Constant being referred to
        Constant,
        
        //! Function to be called
        Function,
        
        //! Opening type of punctuation (like parenthesis, brackets, etc)
        Open,
        
        //! Closing type of punctuation (ie parenthesis, brackets, etc)
        Close
    );

    //! Heavy weight symbol
    struct Symbol {
        std::u32string  text;   // Unfortunately have to be strings not views :(
        SymType         type    = SymType::None;
        
        constexpr bool operator==(const Symbol&) const = default;
    };

    //! Light weight token
    struct Token {
        SymType         type    = SymType::None;
        size_t          len     = 0;
        
        constexpr bool  operator==(const Token&) const noexcept = default;
    };

    using TokenFN   = std::function<std::error_code(SymType,std::u32string_view)>;
    using feature_t = std::pair<bool,size_t>;

    /*! \brief Sub-tokenizes
    
        This is the sub-tokenizer, it scans the text for what seems like the next
        relevant symbol.  
    */
    Token               token(std::u32string_view);

    Expect<SymVector>   tokenize(std::string_view);
    Expect<SymVector>   tokenize(std::u32string_view);

    std::error_code     tokenize(std::u32string_view, TokenFN&&);
    std::error_code     tokenize(std::string_view, TokenFN&&);

    log4cpp::CategoryStream&    operator<<(log4cpp::CategoryStream&, const Symbol&);
    log4cpp::CategoryStream&    operator<<(log4cpp::CategoryStream&, const Token&);
    std::ostream&    operator<<(std::ostream&, const Symbol&);
    std::ostream&    operator<<(std::ostream&, const Token&);
}
