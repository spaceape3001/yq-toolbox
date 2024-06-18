////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <0/basic/TextUtils.hpp>
#include <0/basic/TextUtils32.hpp>
#include <0/math/expr/Symbol.hpp>
//#include <0/expr/Expression.hpp>
#include <iostream>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;
using namespace yq::expr;


std::ostream& operator<<(std::ostream&out, const SymVector& syms)
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
    auto etch = tokenize(uexpr);
    if(!etch){
        std::cerr << "Expression parsing failed!\n";
        return false;
    }
    
    SymVector  x   = *etch;
    bool    success  = is_same(x, match);
    if(! success){
        std::cerr << "Parse failed to match \"" << uexpr << "\" >> " << x << "\n";
    }
    return success;
}


ut::suite tests = []{
    "Tokenize"_test = []{
        expect( token(U"0") == Token{ SymType::Int, 1 });
        expect( token(U"pi") == Token{ SymType::Text, 2 });
        expect( token(U"3pi") == Token{ SymType::Int, 1 });
        expect( token(U".3pi") == Token{ SymType::Float, 2 });
        expect( token(U"+.3pi") == Token{ SymType::Operator, 1 });
        expect( token(U"1e3a") == Token{ SymType::Float, 3 });
        expect( token(U"1e+3a") == Token{ SymType::Float, 4 });
        expect( token(U"1e-3a") == Token{ SymType::Float, 4 });
        expect( token(U"1.e+3a") == Token{ SymType::Float, 5 });
        expect( token(U".1e+3a") == Token{ SymType::Float, 5 });
        expect( token(U"0.1e+3a") == Token{ SymType::Float, 6 });
        expect( token(U"0.1e--3a") == Token{ SymType::Float, 3 });
        expect( token(U"abc3_0.1e--3a") == Token{ SymType::Text, 6 });
    };
    
    "Parse"_test = []{
        expect(parses( "", {}));
        expect(parses( "zero", {{ U"zero", SymType::Text }}));
        expect(parses( "3*x", {{ U"3", SymType::Int }, {U"*", SymType::Operator}, {U"x", SymType::Text}}));
        expect(parses( "a^2", {{ U"a", SymType::Text }, {U"^", SymType::Operator}, {U"2", SymType::Int}}));
        expect(parses( "a^2+y", {{ U"a", SymType::Text }, {U"^", SymType::Operator}, 
            {U"2", SymType::Int}, { U"+", SymType::Operator}, {U"y", SymType::Text}}));
    };
};

int main(){
    return ut::cfg<>.run();
};

