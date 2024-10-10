////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Expect.hpp>
#include <yq/userexpr/forward.hpp>

namespace yq::expr {
    /*! \brief Sub-tokenizes
    
        This is the sub-tokenizer, it scans the text for what seems like the next
        relevant symbol.  
    */
    Token               token(std::u32string_view);
        
    Expect<SymVector>   tokenize(std::string_view);
    Expect<SymVector>   tokenize(std::u32string_view);
        
    std::error_code     tokenize(std::u32string_view, SymVector&);
    std::error_code     tokenize(std::string_view, SymVector&);

    std::error_code     tokenize(std::u32string_view, TokenFN&&);
    std::error_code     tokenize(std::string_view, TokenFN&&);
}
