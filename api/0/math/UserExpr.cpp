////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "UserExprImpl.hpp"
#include <0/basic/errors.hpp>
#include <0/basic/Logging.hpp>
#include <0/basic/Stack.hpp>
#include <0/basic/TextUtils.hpp>
#include <0/basic/TextUtils32.hpp>

namespace yq {
	namespace {
		enum : uint8_t {
			PCompare    = 1,
			PLogic,
			PAddSub,
			PMulDiv,
			PPower
		};

        using feature_t = std::pair<bool,size_t>;

        constexpr bool  is_comma(const UserExpr::Symbol&sym)
        {
            return (sym.category == UserExpr::Symbol::Category::Special) && (sym.kind == UserExpr::Symbol::Kind::Comma);
        }

        constexpr bool	is_comma(const UserExpr::SymCode&sym)
        {
            return (sym.category == UserExpr::Symbol::Category::Special) && (sym.kind == UserExpr::Symbol::Kind::Comma);
        }

        constexpr bool is_starting_term(const UserExpr::SymCode& sc)
        {
            if(sc == UserExpr::SymCode{})
                return true;
            if(sc.category == UserExpr::Symbol::Category::Open)
                return true;
            if(sc.category == UserExpr::Symbol::Category::Operator)
                return true;
            if(is_comma(sc))
                return true;
            return false;
        }
        
        constexpr bool is_ending_term(const UserExpr::SymCode& sc)
        {
            if(sc == UserExpr::SymCode{})
                return true;
            if(sc.category == UserExpr::Symbol::Category::Close)
                return true;
            if(sc.category == UserExpr::Symbol::Category::Operator)
                return true;
            if(is_comma(sc))
                return true;
            return false;
        }
	}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


    UserExpr::Repo&   UserExpr::repo() 
    {   
        return Repo::instance();
    }

//------------------------------------------------------------------------------
//  Tokenization

    UserExpr::Token   UserExpr::token(std::u32string_view in)
    {
        static const Repo& _r = repo();
        
        Token         ret{};
        if(in.empty())
            return ret;
            
        size_t&     cnt = ret.length;
        char32_t    ch  = in[0];
        
        //  white space
        if(is_space(ch)){
            ret.category	= Symbol::Category::Space;
            ret.kind		= Symbol::Kind::None;
            for(cnt = 1; cnt<in.size(); ++cnt){
                if(!is_space(in[cnt]))
                    break;
            }
            return ret;
        }
        
        //  text identifier
        if(is_alpha(ch) || (_r.punctuation_can_start_text() && _r.is_punct_text(ch))){
            ret.category	= Symbol::Category::Text;
            ret.kind		= Symbol::Kind::None;
            for(cnt=1; cnt<in.size(); ++cnt){
                if(is_alpha(in[cnt]))
                    continue;
                if(_r.digits_in_text() && is_digit(in[cnt]))
                    continue;
                if(_r.is_punct_text(in[cnt]))
                    continue;
                break;
            }
            return ret;
        } //    end of alpha

        char32_t    nx  = (in.size() > 1) ? in[1] : '\0';
        
        //  It's a NUMBER
        if(is_digit(ch) || ((ch == '.') && is_digit(nx))){
        
            if( (ch == '0') && ((nx == 'x') || (nx == 'X'))){
                ret.category	= Symbol::Category::Value;
                ret.kind		= Symbol::Kind::Hexadecimal;
                //  it's a hex constant
                for(cnt=2; cnt<in.size(); ++cnt){
                    if(!is_xdigit(in[cnt]))
                        break;
                }
                return ret;
            }
            
            if((ch == '0') && is_digit(nx)){
                ret.category	= Symbol::Category::Value;
                ret.kind		= Symbol::Kind::Octal;
                
                //  it's an octal constant
                for(cnt=2; cnt<in.size(); ++cnt){
                    if(!is_digit(in[cnt]))
                        break;
                }
                
                return ret;
            }
            
            
            //  Ordinary number (may or may not be floating point)
            feature_t  decimal     = {};
            feature_t  exponent    = {};
            feature_t  expsign     = {};
            
            if(ch == '.')
                decimal = { true, 0 };
                
            for(cnt=1;cnt<in.size();++cnt){
            
                //  numbers are always allowed
                if(is_digit(in[cnt]))
                    continue;
                    
                //  decimal... one only
                if(in[cnt] == '.'){
                
                    //  but not after exponents
                    if(exponent.first){
                        if(exponent.second == cnt-1) {
                            cnt = exponent.second;
                        }
                        if(expsign.first && (expsign.second == cnt-1)){
                            cnt = exponent.second;
                        }
                        break;
                    }

                    // duplicate...nope
                    if(decimal.first)
                        break;

                    // record decimal
                    decimal  = { true, cnt };
                    continue;
                }
                
                //      alphabet?
                if(is_alpha(in[cnt])){

                    //  we're already in an exponent?
                    if(exponent.first){
                        //  already marked it exponent, abort
                        
                        if(exponent.second == cnt-1){ // immediately after exponent, scrub out exponent
                            cnt = exponent.second;
                        }
                            
                            //  there was a sign instead?  scrub
                        if(expsign.first && (expsign.second == cnt-1)){   // sign is bad too
                            cnt = exponent.second;
                        }
                        break;
                    }
                    
                    //  if it's exponent character, record
                    if((in[cnt] == 'e') || (in[cnt] == 'E')){
                        exponent    = { true, cnt };
                        continue;
                    }
                    
                    //  otherwise, it's not a value, break
                    break;
                }
                
                if(exponent.first && ((in[cnt] == '-') || (in[cnt] == '+'))){
                    if(expsign.first){
                        if(cnt-1 == expsign.second)
                            cnt = exponent.second;
                        break;
                    }
                    if(cnt-1 != exponent.second){
                        break;
                    }
                    
                    //  It's a sign!
                    expsign = { true, cnt };
                    continue;
                }
                
                //  ANY OTHER CHARACTER BREAKS THIS
                break;
            }
            
            if(decimal.first || exponent.first){
                ret.category	= Symbol::Category::Value;
                ret.kind		= Symbol::Kind::Float;
            } else {
                ret.category	= Symbol::Category::Value;
                ret.kind		= Symbol::Kind::Integer;
            }
            
            return ret;
        }   // end of value test
        
        
        if(is_punct(ch)){
            ret.category	= Symbol::Category::Operator;
            
            size_t cc = 1;
            for(; cc<in.size(); ++cc)
                if(!is_punct(in[cc]))
                    break;
            
            size_t  lc = 0;
            for(; lc<cc; ++lc){
                std::u32string_view part    = in.substr(0,lc+1);
                if(!_r.has_operator(part))
                    break;
            }

            cnt     = lc ? lc : 1;
            return ret;
        }
        
        return Token{ .category=Symbol::Category::Error, .length=1 };
    }

    Expect<UserExpr::SymVector>   UserExpr::tokenize(std::string_view input)
    {
        std::u32string  u32 = to_u32string(input);
        return tokenize(u32);
    }
    
    Expect<UserExpr::SymVector>   UserExpr::tokenize(std::u32string_view input)
    {
        SymVector   ret;
        std::error_code ec  = tokenize(input, ret);
        if(ec != std::error_code())
            return unexpected(ec);
        return ret;
    }

    std::error_code  UserExpr::tokenize(std::u32string_view input, SymVector& tokens)
    {
        return tokenize(input, [&](SymCode c, std::u32string_view s) -> std::error_code {
            tokens.push_back(Symbol{ 
					.category = c.category,
					.kind = c.kind,
					.text = std::u32string(s)
				});
            return std::error_code();
        });
    }
    
    std::error_code  UserExpr::tokenize(std::string_view input, SymVector& tokens)
    {
        std::u32string  u32 = to_u32string(input);
        return tokenize(u32, tokens);
    }
        
    std::error_code  UserExpr::tokenize(std::u32string_view input, TokenFN&&fn)
    {
        if(!fn){
            return errors::bad_argument();
        }
        
        for(std::u32string_view i=input; !i.empty(); ){
            Token   t   = token(i);
            if((t.category == Symbol::Category::Error) || (t.length == 0)){
                return errors::bad_argument();
            }
            
            fn({.category=t.category, .kind = t.kind}, i.substr(0, t.length));
            i = i.substr(t.length);
        }
        return std::error_code();
    }
    
    std::error_code  UserExpr::tokenize(std::string_view input, TokenFN&& fn)
    {
        std::u32string      u32 = to_u32string(input);
        return tokenize(u32, std::move(fn));
    }

//------------------------------------------------------------------------------
//  Streamlining (static user-expr)

    std::error_code  UserExpr::streamline(SymVector& syms)
    {
        std::error_code ec;
        
        ec = s1_open_close(syms);
        if(ec != std::error_code())
            return ec;

        ec = s2_signs(syms);
        if(ec != std::error_code())
            return ec;

        ec = s3_operators(syms);
        if(ec != std::error_code())
            return ec;

        ec = s4_interpret_values(syms);
        if(ec != std::error_code())
            return ec;

        return {};
    }

    std::error_code UserExpr::s1_open_close(SymVector&syms)
    {
		for(Symbol& sym : syms){
			if(sym.text == U","){
				sym.category	= Symbol::Category::Special;
				sym.kind		= Symbol::Kind::Comma;
			}
			if(sym.text == U"("){
				sym.category	= Symbol::Category::Open;
				sym.kind		= Symbol::Kind::Generic;
			}
			if(sym.text == U")"){
				sym.category	= Symbol::Category::Close;
				sym.kind		= Symbol::Kind::Generic;
			}
			if(sym.text == U"["){
				sym.category	= Symbol::Category::Open;
				sym.kind		= Symbol::Kind::Array;
			}
			if(sym.text == U"]"){
				sym.category	= Symbol::Category::Close;
				sym.kind		= Symbol::Kind::Array;
			}
			if(sym.text == U"{"){
				sym.category	= Symbol::Category::Open;
				sym.kind		= Symbol::Kind::Tuple;
			}
			if(sym.text == U"}"){
				sym.category	= Symbol::Category::Close;
				sym.kind		= Symbol::Kind::Tuple;
			}
		}
        return {};
    }
    
    std::error_code UserExpr::s2_signs(SymVector&syms)
    {
		SymCode		last	= {};
		for(auto itr = syms.begin(); itr != syms.end(); last=*itr, ++itr){
			if((itr -> text != U"-") && (itr->text != U"+"))
				continue;
			// This symbol is "-" negative
			if(!is_starting_term(last))
				continue;
			auto jtr = itr + 1;
			if(jtr == syms.end())
				continue;
			if(jtr -> category != Symbol::Category::Value)
				continue;
			if(!((jtr -> kind == Symbol::Kind::Integer) ||  (jtr -> kind == Symbol::Kind::Float))){
				jtr -> kind	= (itr->text == U"-") ? Symbol::Kind::Negate : Symbol::Kind::Affirm;
				continue;
			}
			
			jtr -> text	= itr->text + jtr->text;
			itr = syms.erase(itr);
		}
        return {};
    }
    
    std::error_code UserExpr::s3_operators(SymVector&syms)
    {
        static const Repo& _r = repo();
		SymCode		last	= {};
		for(auto itr = syms.begin(); itr != syms.end(); last=*itr, ++itr){
			if( itr -> category != Symbol::Category::Operator)
				continue;
			if( itr -> kind != Symbol::Kind::None)
				continue;
			const OpData* op = _r.operator_(itr->text);
			if(!op)
				return errors::bad_argument();
			
			itr->category	= op->category;
			itr->kind		= op->kind;
			itr->extra   	= op->priority;
		}
        return {};
    }
    
    std::error_code UserExpr::s4_interpret_values(SymVector&syms)
    {
		for(Symbol& sym : syms) {
			if(sym.category != Symbol::Category::Value)
				continue;
			switch(sym.kind){
			case Symbol::Kind::Integer:
				sym.value	= Any((int64_t) *to_int64(sym.text));
				break;
			case Symbol::Kind::Hexadecimal:
yInfo() << "Hexadecimal... " << sym.text;
				sym.value	= Any((uint64_t) *to_hex64(sym.text.substr(2)));
				break;
			case Symbol::Kind::Float:
				sym.value	= Any((double) *to_integer(sym.text));
				break;
			case Symbol::Kind::Octal:
				sym.value	= Any((uint64_t) *to_octal64(sym.text));
				break;
			default:
				break;
			}
		}
        return {};
    }

//------------------------------------------------------------------------------
//  Algebra to RPN

    std::error_code	UserExpr::algebra_to_rpn(SymVector& rpn, const SymVector& alg)
    {
        SymStack    pending;
        for(const Symbol& sym : alg){
            switch(sym.category){
            case Symbol::Category::None:
                //  ignore
                break;
            case Symbol::Category::Error:
                return errors::bad_userexpr();
            case Symbol::Category::Operator:
                return errors::todo();
            case Symbol::Category::Space:
                //  ignore
                break;
            case Symbol::Category::Text:
                return errors::todo();
            case Symbol::Category::Value:
                rpn.push_back(sym);
                break;
            case Symbol::Category::Open:
                return errors::todo();
            case Symbol::Category::Close:
                return errors::todo();
            case Symbol::Category::Special:
                return errors::todo();
            }
        }
        if(pending.empty())
            return {};
        return errors::bad_userexpr();
    }

//------------------------------------------------------------------------------
//  Execution

    Expect<Any>  UserExpr::execute(u32string_any_map_t&vars, const SymVector& codes)
    {
        any_stack_t     theStack;
        for(const Symbol& x : codes){
            switch(x.category){
            case Symbol::Category::None:
                //  ignore
                break;
            case Symbol::Category::Error:
                return errors::bad_instruction();
            case Symbol::Category::Operator:
                return errors::todo();
            case Symbol::Category::Space:
                //  ignore
                break;
            case Symbol::Category::Text:
                return errors::todo();
            case Symbol::Category::Value:
                theStack << x.value;
                break;
            case Symbol::Category::Open:
                return errors::todo();
            case Symbol::Category::Close:
                return errors::todo();
            case Symbol::Category::Special:
                return errors::todo();
            }
        }

        if(theStack.empty())
            return errors::empty_stack();
        if(theStack.size() > 1)
            return errors::mulitple_values();
        return theStack.pop();
    }

//------------------------------------------------------------------------------

    UserExpr::UserExpr() = default;
    UserExpr::UserExpr(const UserExpr&) = default;
    UserExpr::UserExpr(UserExpr&&) = default;
    UserExpr& UserExpr::operator=(const UserExpr&) = default;
    UserExpr& UserExpr::operator=(UserExpr&&) = default;
    UserExpr::~UserExpr() = default;

    UserExpr::UserExpr(std::string_view sv)
    {
		std::u32string 	u32	= to_u32string(sv);
		m_buildError = _init(u32);
	}
	
    UserExpr::UserExpr(std::u32string_view uin)
    {
		m_buildError = _init(uin);
	}

	std::error_code    UserExpr::_init(std::u32string_view uxpr) 
	{
        std::error_code ec;
		ec	= tokenize(uxpr, m_algebra);
		if(ec != std::error_code())
            return ec;
		
		ec	        = streamline(m_algebra);
		if(ec != std::error_code())
            return ec;
        
        ec      = algebra_to_rpn(m_rpn, m_algebra);
		if(ec != std::error_code())
            return ec;
    
        return {};
	}

    Expect<Any>     UserExpr::evaluate() const
    {
        u32string_any_map_t    variables;
        return evaluate(variables);
    }

    Expect<Any>     UserExpr::evaluate(u32string_any_map_t& variables) const
    {
        if(!is_good())
            return errors::bad_userexpr();
        return execute(variables, m_rpn);
    }


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

    // Table of known operators (this *WILL* grow)
    const UserExpr::OpData             UserExpr::Repo::kStandardOperators[] = {
        { 
			.text 		= U",",  
			.type		= OperatorType::Comma,
			.category 	= Symbol::Category::Special,
			.kind		= Symbol::Kind::Comma
		},
        { 
			.text 		= U":=", 
			.type 		= OperatorType::Set, 
			.category 	= Symbol::Category::Special,
			.kind		= Symbol::Kind::Assign,
			.self 		= true 
		},
		{ 
			.text 		= U"+",  
			.code		= Operator::Add,        
			.type		= OperatorType::Binary, 
			.category	= Symbol::Category::Operator,
			.kind		= Symbol::Kind::Add,
			.priority	= PAddSub 
		},
        { 
			.text 		= U"-",  
			.code 		= Operator::Subtract,   
			.type		= OperatorType::Binary, 
			.category	= Symbol::Category::Operator,
			.kind		= Symbol::Kind::Subtract,
			.priority   = PAddSub 
		},
        { 
			.text 		= U"*",  
			.code		= Operator::Multiply,   
			.type		= OperatorType::Binary, 
			.category	= Symbol::Category::Operator,
			.kind		= Symbol::Kind::Multiply,
			.priority	= PMulDiv 
		},
        { 
			.text 		= U"/",  
			.code		= Operator::Divide,     
			.type		= OperatorType::Binary, 
			.category	= Symbol::Category::Operator,
			.kind		= Symbol::Kind::Divide,
			.priority	= PMulDiv 
		},
        { 
			.text 		= U"^",  
			.code		= Operator::Power,      
			.type		= OperatorType::Binary, 
			.category	= Symbol::Category::Operator,
			.kind		= Symbol::Kind::Power,
			.priority 	= PPower 
		},
        { 
			.text 		= U"⊗",  
			.code 		= Operator::TensorProduct, 
			.type		= OperatorType::Binary, 
			.category	= Symbol::Category::Operator,
			.kind		= Symbol::Kind::TensorProduct,
			.priority	= PMulDiv 
		},
        { 
			.text 		= U"√",  
			.code		= Operator::SquareRoot, 
			.type		= OperatorType::Left, 
			.category	= Symbol::Category::Operator,
			.kind		= Symbol::Kind::SquareRoot,
			.priority	= PPower 
		},
        { 
			.text 		= U"∛",  
			.code		= Operator::CubeRoot,   
			.type		= OperatorType::Left, 
			.category	= Symbol::Category::Operator,
			.kind		= Symbol::Kind::CubeRoot,
			.priority	= PPower 
		},
        { 
			.text 		= U"∜",  
			.code 		= Operator::FourthRoot, 
			.type		= OperatorType::Left, 
			.category	= Symbol::Category::Operator,
			.kind		= Symbol::Kind::FourthRoot,
			.priority	= PPower 
		},
        { 
			.text 		= U"!=", 
			.code		= Operator::NotEqual, 
			.type		= OperatorType::Binary, 
			.category	= Symbol::Category::Operator,
			.kind		= Symbol::Kind::NotEqual,
			.priority	= PCompare 
		},
        { 
			.text 		= U"<>", 
			.code		= Operator::NotEqual, 
			.type 		= OperatorType::Binary, 
			.category	= Symbol::Category::Operator,
			.kind		= Symbol::Kind::NotEqual,
			.priority	= PCompare 
		},
        { 
			.text 		= U"≠",  
			.code 		= Operator::NotEqual, 
			.type		= OperatorType::Binary, 
			.category	= Symbol::Category::Operator,
			.kind		= Symbol::Kind::NotEqual,
			.priority	= PCompare 
		},
        { 
			.text 		= U"<",  
			.code		= Operator::Less, 
			.type		= OperatorType::Binary, 
			.category	= Symbol::Category::Operator,
			.kind		= Symbol::Kind::NotEqual,
			.priority	= PCompare 
		},
        { 
			.text 		= U"<=", 
			.code 		= Operator::LessEqual, 
			.type		= OperatorType::Binary, 
			.category	= Symbol::Category::Operator,
			.kind		= Symbol::Kind::LessEqual,
			.priority 	= PCompare 
		},
        { 
			.text 		= U"≤",  
			.code		= Operator::LessEqual, 
			.type		= OperatorType::Binary, 
			.category	= Symbol::Category::Operator,
			.kind		= Symbol::Kind::LessEqual,
			.priority	= PCompare 
		},
        { 
			.text 		= U">",  
			.code		= Operator::Greater, 
			.type		= OperatorType::Binary, 
			.category	= Symbol::Category::Operator,
			.priority	= PCompare 
		},
        { 
			.text 		= U">=", 
			.code		= Operator::GreaterEqual, 
			.type		= OperatorType::Binary, 
			.category	= Symbol::Category::Operator,
			.priority	= PCompare 
		},
        { 
			.text 		= U"≥",  
			.code		= Operator::GreaterEqual, 
			.type		= OperatorType::Binary, 
			.category	= Symbol::Category::Operator,
			.priority	= PCompare 
		},
        { 
			.text 		= U"(",  
			.type 		= OperatorType::Open, 
			.category	= Symbol::Category::Open,
			.kind		= Symbol::Kind::Generic,
			.other 		= U")" 
		},
        { 
			.text 		= U")",  
			.type 		= OperatorType::Close, 
			.category	= Symbol::Category::Close,
			.kind		= Symbol::Kind::Generic,
			.other 		= U"(" 
		},
        { 
			.text 		= U"[",  
			.type 		= OperatorType::Open, 
			.category	= Symbol::Category::Open,
			.kind		= Symbol::Kind::Array,
			.other 		= U"]" 
		},
        { 
			.text 		= U"]",  
			.type 		= OperatorType::Close, 
			.category	= Symbol::Category::Close,
			.kind		= Symbol::Kind::Array,
			.other 		= U"[" 
		},
        { 
			.text 		= U"{",  
			.type 		= OperatorType::Open, 
			.category	= Symbol::Category::Open,
			.kind		= Symbol::Kind::Tuple,
			.other 		= U"}" 
		},
        { 
			.text 		= U"}",  
			.type 		= OperatorType::Close, 
			.category	= Symbol::Category::Close,
			.kind		= Symbol::Kind::Tuple,
			.other 		= U"{" 
		}
    };

    UserExpr::Repo& UserExpr::Repo::instance()
    {   
        static Repo *s_repo = new Repo;
        return *s_repo;
    }
    
    UserExpr::Repo::Repo() : CompoundInfo("yq::expr::Repo", std::source_location::current())
    {
        m_constants[U"pi"]     = std::numbers::pi_v<double>;
        m_constants[U"sqrt2"]  = std::numbers::sqrt2_v<double>;
        m_constants[U"sqrt3"]  = std::numbers::sqrt3_v<double>;
        m_constants[U"e"]      = std::numbers::e_v<double>;
        m_constants[U"ln2"]    = std::numbers::ln2_v<double>;
        m_constants[U"ln10"]   = std::numbers::ln10_v<double>;
        m_constants[U"egamma"] = std::numbers::egamma_v<double>;
        m_punctText.insert(U'_');

        for(const OpData& d : kStandardOperators){
            m_operators[d.text] = &d;
        }
    }
    
    UserExpr::Repo::~Repo()
    {
    }
    
    void    UserExpr::Repo::sweep_impl()
    {
        for(const Meta* m : children()){
            if(m && m->has(Flag::METHOD)){
                m_functions << static_cast<const MethodInfo*>(m);
            }
            if(m && m->has(Flag::PROPERTY)){
                m_variables << static_cast<const PropertyInfo*>(m);
            }
        }
    }
    
    Expect<Any>     UserExpr::Repo::constant(std::string_view k) const
    {
        std::u32string  k32 = to_u32string(k);
        return constant(k32);
    }
    
    Expect<Any>     UserExpr::Repo::constant(std::u32string_view k) const
    {
        auto i = m_constants.find(std::u32string(k));
        if(i != m_constants.end())
            return i->second;
        return errors::bad_argument();
    }

    bool            UserExpr::Repo::has_constant(std::string_view k) const
    {
        std::u32string  k32 = to_u32string(k);
        return has_constant(k32);
    }
    
    bool            UserExpr::Repo::has_constant(std::u32string_view k) const
    {
        return m_constants.contains(std::u32string(k));
    }

    bool            UserExpr::Repo::has_function(std::string_view k) const
    {
        return m_functions.lut.contains(k);
    }
    
    bool            UserExpr::Repo::has_function(std::u32string_view k) const
    {
        return m_functions.lut32.contains(k);
    }

    bool            UserExpr::Repo::has_operator(std::string_view k) const
    {
        std::u32string  k32 = to_u32string(k);
        return m_operators.contains(k32);
    }

    bool            UserExpr::Repo::has_operator(std::u32string_view k) const
    {
        return m_operators.contains(k);
    }
    
    bool            UserExpr::Repo::has_variable(std::string_view k) const
    {
        return m_variables.lut.contains(k);
    }
    
    bool            UserExpr::Repo::has_variable(std::u32string_view k) const
    {
        return m_variables.lut32.contains(k);
    }

    bool            UserExpr::Repo::is_punct_text(char32_t ch) const
    {
        return m_punctText.contains(ch);
    }

	const UserExpr::OpData*	UserExpr::Repo::operator_(std::u32string_view k) const
	{
		auto itr = m_operators.find(k);
		if(itr != m_operators.end())
			return (itr->second);
		return nullptr;
	}

    Expect<Any>     UserExpr::Repo::variable(std::string_view k) const
    {
        auto i = m_variables.lut.find(k);
        if(i != m_variables.lut.end() && i->second)
            return i->second->get(nullptr);
        return errors::bad_argument();
    }
    
    Expect<Any>     UserExpr::Repo::variable(std::u32string_view k) const
    {
        auto i = m_variables.lut32.find(k);
        if(i != m_variables.lut32.end() && i->second)
            return i->second->get(nullptr);
        return errors::bad_argument();
    }
    
////////////////////////////////////////////////////////////////////////////////

    template <typename S>   void stream_out(S& out, const UserExpr::Symbol& sym)
    {
        out << "{" << key(sym.category) << "/" << key(sym.kind) << ": " << sym.text << "}";
    }

    log4cpp::CategoryStream&    operator<<(log4cpp::CategoryStream&out, const UserExpr::Symbol&sym)
    {
        stream_out(out, sym);
        return out;
    }
    
    std::ostream&    operator<<(std::ostream& out, const UserExpr::Symbol& sym)
    {
        stream_out(out, sym);
        return out;
    }

    template <typename S>   void stream_out(S& out, const UserExpr::SymVector& syms)
    {
        out << "[";
        bool    f   = true;
        for(const UserExpr::Symbol& s : syms){
            if(f){
                f   = false;
            } else
                out << ", ";
            out << s;
        }
        out << "]";
    }

    log4cpp::CategoryStream&    operator<<(log4cpp::CategoryStream&out, const UserExpr::SymVector&syms)
    {
        stream_out(out, syms);
        return out;
    }
    

    std::ostream&    operator<<(std::ostream&out, const UserExpr::SymVector&syms)
    {
        stream_out(out, syms);
        return out;
    }
    
    template <typename S> void stream_out(S&out, const UserExpr::Token& tok)
    {
        out << "{" << key(tok.category) << "/" << key(tok.kind) << ": " << tok.length << "}";
    }

    log4cpp::CategoryStream&    operator<<(log4cpp::CategoryStream& out, const UserExpr::Token& tok)
    {
        stream_out(out, tok);
        return out;
    }

    std::ostream&    operator<<(std::ostream&out, const UserExpr::Token&tok)
    {
        stream_out(out, tok);
        return out;
    }
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#if 0
namespace yq::expr {

	void            zuserexpr::makeRpn()
	{
		m_rpn.clear();
		m_rpn.reserve(m_algebra.size());
		zstack<Operation*>     stk;
		Operation*               u;
		
		for(Symbol* s : m_algebra){
			if(!s)
				continue;
				
			switch( s-> type){
			case ST_None:
				break;
			case ST_Operator:
				u   = static_cast<Operation*>(s);
				if(!u)          // bad....
					break;
				
				for(;;){
					if(stk.empty())
						break;
					   
					Operation* p   = stk.top(nullptr);
					if(p->type == ST_Open)
						break;
					if((p->type == ST_Operator) && (p->priority < u->priority))
						break;
					m_rpn << stk.pop();
				}
				stk << u;
				break;
			case ST_Function:
				stk << static_cast<Operation*>(s);
				break;
			case ST_Value:
			case ST_Variable:
				m_rpn << s;
				break;
			case ST_Open:
				stk << static_cast<Operation*>(s);
				break;
			case ST_Close:
				while(!stk.empty() && stk.top()->type != ST_Open){
					m_rpn << stk.pop();
				}
				break;
			}
		}
		
		while(!stk.empty()){
			m_rpn << stk.pop();
		}
	}

    Expect<SymVector>	compile_rpn(const SymVector& input)
    {
		SymVector		ret;
		Stack<SymData>	stack;
		static auto& _r	= expr::repo();
		
		for(const Symbol& sym : input){
			switch(sym.category){
			case Symbol::Category::None:
			case Symbol::Category::Error:
				break;
			case Symbol::Category::Value:
				ret.push_back(sym);
				break;
			}
		}
		
		return errors::todo();
	}
}
#endif
