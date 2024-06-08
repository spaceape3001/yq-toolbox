////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/expr/preamble.hpp>
#include <0/basic/preamble.hpp>

namespace yq::expr {
    struct Symbol {
        std::u32string  text;   // Unfortunately have to be strings not views :(
        SymType         type    = SymType::None;
        
        constexpr bool operator==(const Symbol&) const = default;
    };

    /*! \brief Expression of user intent
    */
    class Expression {
    public:
    
        static Expect<Expression>   parse(std::string_view, const Grammar& g=default_grammar());
        static Expect<Expression>   parse(std::u32string_view, const Grammar& g=default_grammar());
    
        const std::u32string&       definition() const { return m_definition; }
        const std::vector<Symbol>&  symbols() const { return m_symbols; }
        
        Expression();
        Expression(const Expression&);
        Expression(Expression&&);
        Expression& operator=(const Expression&);
        Expression& operator=(Expression&&);
        ~Expression();
    
        bool    operator==(const Expression&) const;
    
    private:
        explicit Expression(std::u32string_view);

        std::u32string      m_definition;
        std::vector<Symbol> m_symbols;
    };
}
