////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <0/basic/TextUtils.hpp>
#include <0/expr/Grammar.hpp>
#include <0/expr/Expression.hpp>
#include <iostream>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;
using namespace yq::expr;

std::ostream& operator<<(std::ostream&out, SymType st)
{
    switch(st){
    case SymType::None:
        out << "None";
        break;
    case SymType::Value:
        out << "Value";
        break;
    case SymType::Error:
        out << "Error";
        break;
    case SymType::Space:
        out << "Space";
        break;
    case SymType::Text:
        out << "Text";
        break;
    case SymType::Variable:
        out << "Variable";
        break;
    case SymType::Function:
        out << "Function";
        break;
    case SymType::Open:
        out << "Open";
        break;
    case SymType::Close:
        out << "Close";
        break;
    default:
        out << "???";
        break;
    }
    return out;
}

std::ostream& operator<<(std::ostream&out, const Symbol& sym)
{
    std::string     st  = to_string(sym.text);
    out << "{" << sym.type << ": " << st << "}";
    return out;
}

std::ostream& operator<<(std::ostream&out, const std::vector<Symbol>& syms)
{
    out << "[";
    bool    f   = true;
    for(const Symbol& s : syms){
        if(f){
            f   = false;
        } else
            out << ", ";
        out << s;
    }
    out << "]";
    return out;
}

bool is_same(const std::vector<Symbol>& result, std::initializer_list<Symbol> match)
{
    std::span<const Symbol> mm  =   span(match);
    if(result.size() != mm.size())
        return false;
    for(size_t  n=0;n<result.size();++n){
        if(result[n] != mm[n])
            return false;
    }
    return true;
}


bool    parses(const std::string_view uexpr, std::initializer_list<Symbol> match)
{
    auto etch = Expression::parse(uexpr);
    if(!etch){
        std::cerr << "Expression parsing failed!\n";
        return false;
    }
    
    Expression  x   = *etch;
    bool    success  = is_same(x.symbols(), match);
    if(! success){
        std::cerr << "Parse failed to match \"" << uexpr << "\" >> " << x.symbols() << "\n";
    }
    return success;
}


ut::suite tests = []{
    "Tokenize"_test = []{
        const Grammar&  defGram = default_grammar();
        
        expect( defGram.next_token(U"0") == Token{ 1, SymType::Value });
        expect( defGram.next_token(U"pi") == Token{ 2, SymType::Text });
        expect( defGram.next_token(U"3pi") == Token{ 1, SymType::Value });
        expect( defGram.next_token(U".3pi") == Token{ 2, SymType::Value });
        expect( defGram.next_token(U"+.3pi") == Token{ 1, SymType::Operator });
        expect( defGram.next_token(U"1e3a") == Token{ 3, SymType::Value });
        expect( defGram.next_token(U"1e+3a") == Token{ 4, SymType::Value });
        expect( defGram.next_token(U"1e-3a") == Token{ 4, SymType::Value });
        expect( defGram.next_token(U"1.e+3a") == Token{ 5, SymType::Value });
        expect( defGram.next_token(U".1e+3a") == Token{ 5, SymType::Value });
        expect( defGram.next_token(U"0.1e+3a") == Token{ 6, SymType::Value });
        expect( defGram.next_token(U"0.1e--3a") == Token{ 3, SymType::Value });
        expect( defGram.next_token(U"abc3_0.1e--3a") == Token{ 6, SymType::Text });
    };
    
    "Parse"_test = []{
        expect(parses( "", {}));
        expect(parses( "zero", {{ U"zero", SymType::Text }}));
        expect(parses( "3*x", {{ U"3", SymType::Value }, {U"*", SymType::Operator}, {U"x", SymType::Text}}));
        expect(parses( "a^2", {{ U"a", SymType::Text }, {U"^", SymType::Operator}, {U"2", SymType::Value}}));
        expect(parses( "a^2+y", {{ U"a", SymType::Text }, {U"^", SymType::Operator}, 
            {U"2", SymType::Value}, { U"+", SymType::Operator}, {U"y", SymType::Text}}));
    };
};

int main(){
    return ut::cfg<>.run();
};

