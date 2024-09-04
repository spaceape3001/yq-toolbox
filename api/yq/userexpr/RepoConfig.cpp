////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/basic/DelayInit.hpp>
#include <yq/userexpr/impl/Repo.hpp>
#include <yq/math/trigonometry.hpp>

using namespace yq;
using namespace yq::expr;

namespace {

    enum : uint8_t {
        PCompare    = 1,
        PLogic,
        PAddSub,
        PMulDiv,
        PPower
    };

    // Table of known operators (this *WILL* grow)
    const OpData             kStandardOperators[] = {
        { 
			.text 		= U",",  
			.type		= OperatorType::Comma,
			.category 	= SymCategory::Special,
			.kind		= SymKind::Comma
		},
        { 
			.text 		= U":=", 
			.type 		= OperatorType::Set, 
			.category 	= SymCategory::Special,
			.kind		= SymKind::Assign,
			.self 		= true 
		},
		{ 
			.text 		= U"+",  
			.code		= Operator::Add,        
			.type		= OperatorType::Binary, 
			.category	= SymCategory::Operator,
			.kind		= SymKind::Add,
			.priority	= PAddSub,
            .args       = 2
		},
        { 
			.text 		= U"-",  
			.code 		= Operator::Subtract,   
			.type		= OperatorType::Binary, 
			.category	= SymCategory::Operator,
			.kind		= SymKind::Subtract,
			.priority   = PAddSub,
            .args       = 2 
		},
        {
            .text       = U"negate",
            .code       = Operator::Negate,
            .type       = OperatorType::Left,
            .category   = SymCategory::Operator,
            .kind       = SymKind::Negate,
            .priority   = PMulDiv,
            .args       = 1
        },
        {
            .text       = U"affirm",
            .code       = Operator::Affirm,
            .type       = OperatorType::Left,
            .category   = SymCategory::Operator,
            .kind       = SymKind::Affirm,
            .priority   = PMulDiv,
            .args       = 1
        },
        { 
			.text 		= U"*",  
			.code		= Operator::Multiply,   
			.type		= OperatorType::Binary, 
			.category	= SymCategory::Operator,
			.kind		= SymKind::Multiply,
			.priority	= PMulDiv,
            .args       = 2
		},
        { 
			.text 		= U"/",  
			.code		= Operator::Divide,     
			.type		= OperatorType::Binary, 
			.category	= SymCategory::Operator,
			.kind		= SymKind::Divide,
			.priority	= PMulDiv,
            .args       = 2 
		},
        { 
			.text 		= U"^",  
			.code		= Operator::Power,      
			.type		= OperatorType::Binary, 
			.category	= SymCategory::Operator,
			.kind		= SymKind::Power,
			.priority 	= PPower,
            .args       = 2
		},
        { 
			.text 		= U"\u2297",  
			.code 		= Operator::TensorProduct, 
			.type		= OperatorType::Binary, 
			.category	= SymCategory::Operator,
			.kind		= SymKind::TensorProduct,
			.priority	= PMulDiv,
            .args       = 2
		},
        { 
			.text 		= U"\u221a",  
			.code		= Operator::SquareRoot, 
			.type		= OperatorType::Left, 
			.category	= SymCategory::Operator,
			.kind		= SymKind::SquareRoot,
			.priority	= PPower,
            .args       = 1
		},
        { 
			.text 		= U"\u221b",  
			.code		= Operator::CubeRoot,   
			.type		= OperatorType::Left, 
			.category	= SymCategory::Operator,
			.kind		= SymKind::CubeRoot,
			.priority	= PPower 
		},
        { 
			.text 		= U"\u221c",  
			.code 		= Operator::FourthRoot, 
			.type		= OperatorType::Left, 
			.category	= SymCategory::Operator,
			.kind		= SymKind::FourthRoot,
			.priority	= PPower 
		},
        { 
			.text 		= U"!=", 
			.code		= Operator::NotEqual, 
			.type		= OperatorType::Binary, 
			.category	= SymCategory::Operator,
			.kind		= SymKind::NotEqual,
			.priority	= PCompare,
            .args       = 2
		},
        { 
			.text 		= U"<>", 
			.code		= Operator::NotEqual, 
			.type 		= OperatorType::Binary, 
			.category	= SymCategory::Operator,
			.kind		= SymKind::NotEqual,
			.priority	= PCompare,
            .args       = 2
		},
        { 
			.text 		= U"\u2260",  
			.code 		= Operator::NotEqual, 
			.type		= OperatorType::Binary, 
			.category	= SymCategory::Operator,
			.kind		= SymKind::NotEqual,
			.priority	= PCompare,
            .args       = 2
		},
        { 
			.text 		= U"<",  
			.code		= Operator::Less, 
			.type		= OperatorType::Binary, 
			.category	= SymCategory::Operator,
			.kind		= SymKind::NotEqual,
			.priority	= PCompare,
            .args       = 2
		},
        { 
			.text 		= U"<=", 
			.code 		= Operator::LessEqual, 
			.type		= OperatorType::Binary, 
			.category	= SymCategory::Operator,
			.kind		= SymKind::LessEqual,
			.priority 	= PCompare,
            .args       = 2
		},
        { 
			.text 		= U"\u2264",  
			.code		= Operator::LessEqual, 
			.type		= OperatorType::Binary, 
			.category	= SymCategory::Operator,
			.kind		= SymKind::LessEqual,
			.priority	= PCompare,
            .args       = 2
		},
        { 
			.text 		= U">",  
			.code		= Operator::Greater, 
			.type		= OperatorType::Binary, 
			.category	= SymCategory::Operator,
			.priority	= PCompare,
            .args       = 2
		},
        { 
			.text 		= U">=", 
			.code		= Operator::GreaterEqual, 
			.type		= OperatorType::Binary, 
			.category	= SymCategory::Operator,
			.priority	= PCompare,
            .args       = 2
		},
        { 
			.text 		= U"\u2265",  
			.code		= Operator::GreaterEqual, 
			.type		= OperatorType::Binary, 
			.category	= SymCategory::Operator,
			.priority	= PCompare,
            .args       = 2
		},
        { 
			.text 		= U"(",  
			.type 		= OperatorType::Open, 
			.category	= SymCategory::Open,
			.kind		= SymKind::Generic,
			.other 		= U")" 
		},
        { 
			.text 		= U")",  
			.type 		= OperatorType::Close, 
			.category	= SymCategory::Close,
			.kind		= SymKind::Generic,
			.other 		= U"(" 
		},
        { 
			.text 		= U"[",  
			.type 		= OperatorType::Open, 
			.category	= SymCategory::Open,
			.kind		= SymKind::Array,
			.other 		= U"]" 
		},
        { 
			.text 		= U"]",  
			.type 		= OperatorType::Close, 
			.category	= SymCategory::Close,
			.kind		= SymKind::Array,
			.other 		= U"[" 
		},
        { 
			.text 		= U"{",  
			.type 		= OperatorType::Open, 
			.category	= SymCategory::Open,
			.kind		= SymKind::Tuple,
			.other 		= U"}" 
		},
        { 
			.text 		= U"}",  
			.type 		= OperatorType::Close, 
			.category	= SymCategory::Close,
			.kind		= SymKind::Tuple,
			.other 		= U"{" 
		}
    };

    double   fn_abs(double v)
    {
        return ::fabs(v);
    }

    double    fn_atan2(double y, double x)
    {
        return atan(y,x).value;
    }

    double    fn_atan2d(double y, double x)
    {
        return Degree(atan(y,x)).value;
    }
    
    double fn_cbrt(double v)
    {
        return ::cbrt(v);
    }
    
    double fn_cos(double v)
    {
        return cos(Radian(v));
    }
    
    double fn_cosd(double v)
    {
        return cos(Degree(v));
    }
    
    double  fn_hypot(double x, double y)
    {
        return ::hypot(x, y);
    }

    double  fn_log(double v)
    {
        return ::log(v);
    }

    double  fn_log2(double v)
    {
        return ::log2(v);
    }

    double  fn_log10(double v)
    {
        return ::log10(v);
    }
    
    double  fn_log1p(double v)
    {
        return ::log1p(v);
    }

    double  fn_sin(double v)
    {
        return sin(Radian(v));
    }

    double  fn_sind(double v)
    {
        return sin(Degree(v));
    }

    double  fn_sqrt(double x)
    {
        return ::sqrt(x);
    }
    
    double  fn_time() 
    {
        time_t  now;
        time(&now);
        return (double) now;
    }
        
    void reg_std_functions()
    {
        auto w = writer<expr::Repo>();
        
        w.constant("pi", Any(std::numbers::pi_v<double>));
        w.constant("sqrt2", Any(std::numbers::sqrt2_v<double>));
        w.constant("sqrt3", Any(std::numbers::sqrt3_v<double>));
        w.constant("e", Any(std::numbers::e_v<double>));
        w.constant("ln2", Any(std::numbers::ln2_v<double>));
        w.constant("ln10", Any(std::numbers::ln10_v<double>));
        w.constant("egamma", Any(std::numbers::egamma_v<double>));

        w.punct2text(U'_');
        w.operands(kStandardOperators);
        
        w.function("abs", fn_abs);
        w.function("atan2", fn_atan2);
        w.function("atan2d", fn_atan2d);
        w.function("cbrt", fn_cbrt);
        w.function("cos", fn_cos);
        w.function("cosd", fn_cosd);
        w.function("hypot", fn_hypot);
        w.function("log", fn_log);
        w.function("log10", fn_log10);
        w.function("log1p", fn_log1p);
        w.function("log2", fn_log2);
        w.function("sin", fn_sin);
        w.function("sind", fn_sind);
        w.function("sqrt", fn_sqrt);
        w.function("time", fn_time);
    }

    YQ_INVOKE( reg_std_functions(); )
}
