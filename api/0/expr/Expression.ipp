////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Expression.hpp"
#include <0/basic/errors.hpp>
#include <0/basic/TextUtils.hpp>

namespace yq::expr {
    Expect<Expression>   Expression::parse(std::string_view sv, const Grammar& g)
    {
        std::u32string      s   = to_u32string(sv);
        return parse(s, g);
    }
    
    Expect<Expression>   Expression::parse(std::u32string_view in, const Grammar& g)
    {
        Expression  ret(in);
        
        std::u32string_view    remainder    = ret.m_definition;
        while(!remainder.empty()){
            Token   tok = g.next_token(remainder);
            if((tok.type == SymType::Error) || (tok.len == 0)){
                return errors::bad_argument();
            }
            
            Symbol  sym { std::u32string(remainder.substr(0, tok.len)), tok.type };
            remainder   = remainder.substr(tok.len);
            ret.m_symbols.push_back(sym);
        }
        
        return ret;
    }
    
    ////////////////////////////////////////////////////////////////////////////////
    
    Expression::Expression(std::u32string_view sv) : m_definition(sv)
    {
    }

    Expression::Expression() = default;
    Expression::Expression(const Expression&) = default;
    Expression::Expression(Expression&&) = default;
    Expression& Expression::operator=(const Expression&) = default;
    Expression& Expression::operator=(Expression&&) = default;
    Expression::~Expression() = default;
    bool    Expression::operator==(const Expression&) const = default;

}
