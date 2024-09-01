////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
//#include <0/basic/CollectionUtils.hpp>
#include <yq/basic/Logging.hpp>
#include <0/basic/TextUtils.hpp>
#include <0/basic/TextUtils32.hpp>
#include <0/math/expr/Repo.hpp>
#include <0/math/expr/Token.hpp>
#include <0/math/expr/Tokenize.hpp>
#include <0/math/UserExprImpl.hpp>
#include <iostream>
#include <cmath>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;
using namespace yq::expr;

#if 0
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
#endif

bool    sdouble(std::string_view ustr, double val, double ep=1e-14)
{
    UserExpr    ux(ustr);
    if(!ux.is_good()){
        std::cerr << "Expression initialization failed: " << ux.build_error().message() << "\n";
        return false;
    }
    
    auto valx    = ux.evaluate();
    if(!valx){
        std::cerr << "Expression evaluation failed: " << valx.error().message() << "\n";
        return false;
    }
    
    auto dd = to_double(*valx);
    if(!dd){
        std::cerr << "Extraction of value failed: " << dd.error().message() << "\n";
        return false;
    }
    
    if(::fabs(*dd - val) <= ep){
        return true;
    }
    
    std::cerr << "Evalulation failed on \"" << ustr << "\" to produce: " << *dd << " instead of " << val << "\n";
    return false;
}

int main()
{
    log_to_std_error();
    Meta::freeze();

    "Has Operator"_test = []{
        auto& _r    = expr::Repo::instance();
        expect( true == _r.has_operator("+"));
        expect( false == _r.has_operator("+."));
        expect( false == _r.has_operator("+*"));
        expect( true == _r.has_operator("-"));
        expect( false == _r.has_operator("-*"));
        expect( false == _r.has_operator("-."));
    };
    
    
		// disabled until the overhaul is finished (chris -- 26 Jul 2024)
    "Tokenize"_test = []{
        expect(token(U"0") == Token{ 
			.category	= SymCategory::Value, 
			.kind		= SymKind::Integer, 
			.length 	= 1 
		});
        expect(token(U"(") == Token{ 
			.category	= SymCategory::Open, 
			.kind		= SymKind::Generic, 
			.length 	= 1 
		});
        expect(token(U")") == Token{ 
			.category	= SymCategory::Close, 
			.kind		= SymKind::Generic, 
			.length 	= 1 
		});
        expect(token(U"0x1") == Token{ 
			.category	= SymCategory::Value,
			.kind		= SymKind::Hexadecimal,
			.length 	= 3 
		});
        expect(token(U"0xA") == Token{
			.category	= SymCategory::Value,
			.kind		= SymKind::Hexadecimal,
			.length 	= 3 
		});
        expect(token(U"001") == Token{ 
			.category 	= SymCategory::Value,
			.kind 		= SymKind::Octal,
			.length 	= 3 
		});
        expect(token(U"pi") == Token{ 
			.category	= SymCategory::Text,
			.kind		= SymKind::None,
			.length		= 2 
		});
        expect(token(U"3pi") == Token{ 
			.category	= SymCategory::Value,
			.kind		= SymKind::Integer,
			.length		= 1 
		});
        expect(token(U".3pi") == Token{ 
			.category	= SymCategory::Value,
			.kind		= SymKind::Float,
			.length		= 2 
		});
        expect(token(U"3.5") == Token{ 
			.category	= SymCategory::Value,
			.kind		= SymKind::Float,
			.length		= 3
		});
        expect(token(U"+.3pi") == Token{ 
			.category	= SymCategory::Operator,
			.kind		= SymKind::Add,
			.length		= 1
		});
        expect(token(U"1e3a") == Token{ 
			.category	= SymCategory::Value,
			.kind		= SymKind::Float,
			.length		= 3 
		});
        expect(token(U"1e+3a") == Token{ 
			.category	= SymCategory::Value,
			.kind		= SymKind::Float,
			.length		= 4 
		});
        expect(token(U"1e-3a") == Token{ 
			.category	= SymCategory::Value,
			.kind		= SymKind::Float,
			.length		= 4 
		});
        expect(token(U"1.e+3a") == Token{ 
			.category	= SymCategory::Value,
			.kind		= SymKind::Float,
			.length		= 5 
		});
        expect(token(U".1e+3a") == Token{ 
			.category	= SymCategory::Value,
			.kind		= SymKind::Float,
			.length		= 5 
		});
        expect(token(U"0.1e+3a") == Token{ 
			.category	= SymCategory::Value,
			.kind		= SymKind::Float,
			.length		= 6 
		});
        expect(token(U"0.1e--3a") == Token{ 
			.category	= SymCategory::Value,
			.kind		= SymKind::Float,
			.length		= 3 
		});
        expect(token(U"abc3_0.1e--3a") == Token{ 
			.category	= SymCategory::Text,
			.kind		= SymKind::None,
			.length		= 6 
		});
    };
    
    #if 0
    "Parse"_test = []{
        expect(parses( "", {}));
        expect(parses( "zero", {{ U"zero", SymType::Text }}));
        expect(parses( "3*x", {{ U"3", SymType::Int }, {U"*", SymType::Operator}, {U"x", SymType::Text}}));
        expect(parses( "a^2", {{ U"a", SymType::Text }, {U"^", SymType::Operator}, {U"2", SymType::Int}}));
        expect(parses( "a^2+y", {{ U"a", SymType::Text }, {U"^", SymType::Operator}, 
            {U"2", SymType::Int}, { U"+", SymType::Operator}, {U"y", SymType::Text}}));
    };
    #endif
    
    "Evaluate Simple Double Result"_test = []{
        expect(sdouble("0.", 0.));
        expect(sdouble("1.0", 1.));
        expect(sdouble("3.5", 3.5));
        expect(sdouble("0x1", 1.));
        expect(sdouble("(0x1)", 1.));
        expect(sdouble("[0x1]", 1.));
        expect(sdouble("10.0", 10.));
        expect(sdouble("(10.0)", 10.));
        expect(sdouble("({10.0})", 10.));
        expect(sdouble("({[10.0]})", 10.));
        expect(sdouble("10", 10.));
        expect(sdouble("0XA", 10.));
        expect(sdouble("012", 10.));
        expect(sdouble("0.+0.", 0.));
        expect(sdouble("1.+0.", 1.));
        expect(sdouble("0.+1.", 1.));
        expect(sdouble("1.+1.", 2.));
        expect(sdouble("2*3.5", 7.));
        expect(sdouble("14./2", 7.));
        expect(sdouble("1.5^2", 2.25));
        expect(sdouble("pi", std::numbers::pi_v<double>));
        expect(sdouble("2*pi", 2.0*std::numbers::pi_v<double>));
        expect(sdouble("sqrt(4)", 2.0));
        expect(sdouble("sqrt(25)", 5.0));
    };
    
    #if 0
    "Evaluate Addition"_test = []{
    };
    #endif

    return ut::cfg<>.run();
};

