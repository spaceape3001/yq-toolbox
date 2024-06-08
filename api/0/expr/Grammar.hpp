////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <0/expr/preamble.hpp>
#include <system_error>
#include <unordered_set>
#include <map>

namespace yq::expr {

    struct Token {
        size_t              len     = 0;
        SymType             type    = SymType::None;
        
        constexpr bool  operator==(const Token&) const noexcept = default;
    };

    class Grammar {
    public:
        using OpMap         = std::map<std::u32string_view, const void*>;
        //using U32ViewSet    = std::set<std::u32string_view>;
        using C32Hash       = std::unordered_set<char32_t>;
        //using U32Hash       = std::unordered_set<char32_t>;
    
        //u32string_set_t     open;
        //u32string_set_t     close;
        
        Token   next_token(std::u32string_view) const;
    
        Grammar();
        ~Grammar();
    
        //! Adds the character to the list of valid function/variable/constant names
        //! (ie, '_')
        void        add_punct_text(char32_t);
        
    
    private:
        OpMap       m_operators;
        
        //! Punctuation symbols valid for text (not starting though)
        C32Hash     m_punctText;
        
        //! TRUE means numbers after first letter are treated as part of names
        bool        m_digitsText    = true;
        
        //! If TRUE, means punctuation can start text
        bool        m_punctStartText    = true;
    };
}
