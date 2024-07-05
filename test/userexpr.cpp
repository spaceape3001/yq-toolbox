////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <0/basic/Logging.hpp>
#include <0/basic/TextUtils.hpp>
#include <0/basic/TextUtils32.hpp>
#include <0/math/expr/Repo.hpp>
#include <0/math/expr/Symbol.hpp>
#include <0/math/expr/Instruction.hpp>
#include <iostream>
#include <cmath>

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

bool    sdouble(std::string_view ux, double val, double ep=1e-14)
{
    auto toks   = tokenize(ux);
    if(!toks){
        std::cerr << "Expression parsing failed: " << toks.error().message() << "\n";
        return false;
    }
    
    auto ccx    = compile(*toks);
    if(!ccx){
        std::cerr << "Expression compiling failed: " << ccx.error().message() << "\n";
        return false;
    }
    
    auto valx    = evaluate(*ccx);
    if(!valx){
        std::cerr << "Expression evaluation failed: " << valx.error().message() << "\n";
        return false;
    }
    
    auto dd = to_double(*valx);
    if(!dd){
        std::cerr << "Extraction of value failed: " << dd.error().message() << "\n";
        return false;
    }
    
    return ::fabs(*dd - val) <= ep;
}

ut::suite tests = []{
    "Has Operator"_test = []{
        auto& _r    = Repo::instance();
        expect( true == _r.has_operator("+"));
        expect( false == _r.has_operator("+."));
        expect( false == _r.has_operator("+*"));
        expect( true == _r.has_operator("-"));
        expect( false == _r.has_operator("-*"));
        expect( false == _r.has_operator("-."));
    };

    "Tokenize"_test = []{
        expect( token(U"0") == Token{ SymType::Int, 1 });
        expect( token(U"0x1") == Token{ SymType::Hex, 3 });
        expect( token(U"0xA") == Token{ SymType::Hex, 3 });
        expect( token(U"001") == Token{ SymType::Octal, 3 });
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
    
    "Evaluate Simple"_test = []{
        expect(sdouble("0.", 0.));
        expect(sdouble("1.0", 1.));
        expect(sdouble("0x1", 1.));
        expect(sdouble("10.0", 10.));
        expect(sdouble("10", 10.));
        expect(sdouble("0XA", 10.));
        expect(sdouble("012", 10.));
        expect(sdouble("pi", std::numbers::pi_v<double>));
    };
    
    "Evaluate Addition"_test = []{
        expect(sdouble("0.+0.", 0.));
        expect(sdouble("1.+0.", 1.));
        expect(sdouble("0.+1.", 1.));
        expect(sdouble("1.+1.", 2.));
    };
};

int main(){
    log_to_std_error();
    return ut::cfg<>.run();
};

