////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "UserExprImpl.hpp"

#include <0/basic/errors.hpp>
#include <0/basic/DelayInit.hpp>
#include <0/basic/Logging.hpp>
#include <0/basic/Stack.hpp>
#include <0/basic/TextUtils.hpp>
#include <0/basic/TextUtils32.hpp>
#include <0/meta/ArgInfo.hpp>
#include <0/meta/ConstructorInfo.hpp>
#include <0/meta/OperatorInfo.hpp>
#include <0/meta/TypeInfo.hpp>


namespace yq::expr {
    namespace {
        using feature_t = std::pair<bool,size_t>;

		enum : uint8_t {
			PCompare    = 1,
			PLogic,
			PAddSub,
			PMulDiv,
			PPower
		};


        constexpr bool  is_comma(const Symbol&sym)
        {
            return (sym.category == SymCategory::Special) && (sym.kind == SymKind::Comma);
        }

        constexpr bool	is_comma(const SymCode&sym)
        {
            return (sym.category == SymCategory::Special) && (sym.kind == SymKind::Comma);
        }

        constexpr bool is_starting_term(const SymCode& sc)
        {
            if(sc == SymCode{})
                return true;
            if(sc.category == SymCategory::Open)
                return true;
            if(sc.category == SymCategory::Operator)
                return true;
            if(is_comma(sc))
                return true;
            return false;
        }
        
        constexpr bool is_ending_term(const SymCode& sc)
        {
            if(sc == SymCode{})
                return true;
            if(sc.category == SymCategory::Close)
                return true;
            if(sc.category == SymCategory::Operator)
                return true;
            if(is_comma(sc))
                return true;
            return false;
        }

    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Instruction::Instruction(const string_t& _text) : m_text(_text)
    {
    }
    
    Instruction::~Instruction()
    {
    }

    Instruction::result_t    Instruction::result() const
    {
        return {};
    }
    
        
    Instruction::result_t    Instruction::result(std::span<const TypeInfo*>) const
    {
        return result();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    class AssignInstruction : public Instruction {
    public:
        AssignInstruction(const string_t& s) : Instruction(s)
        {
        }
        
        ~AssignInstruction(){}
        
        std::error_code     execute(Context& ctx) const override
        {
            if(ctx.values.empty()){
                return errors::empty_stack();
            }
            
            ctx.variables[m_text]  = ctx.values.pop();
            return {};
        }

        result_t    result() const override
        {
            return -1;
        }
    };
    
    class DuplicateInstruction : public Instruction {
    public:
        DuplicateInstruction(const string_t s) : Instruction(s)
        {
        }
        
        ~DuplicateInstruction(){}
        
        virtual std::error_code     execute(Context&ctx) const override
        {
            if(ctx.values.empty()){
                return errors::empty_stack();
            }
            
            ctx.values << ctx.values.top();
            return {};
        }
        
        result_t   result() const override 
        { 
            return 1; 
        }
    };

    class NullInstruction : public Instruction {
    public:
        NullInstruction(const string_t&s) : Instruction(s) 
        {
        }
        
        ~NullInstruction(){}
        
        std::error_code     execute(Context&ctx) const override
        {
            return {};
        }

        result_t   result() const override 
        { 
            return 0; 
        }
    };
    
    class OperatorInstruction : public Instruction {
    public:
    
        OperatorInstruction(const string_t& s, Operator opcode) : Instruction(s), m_operator(opcode)
        {
        }
        
        std::error_code     execute(Context&) const override
        {
            return errors::todo();
        }

        Operator m_operator;
    };
    
    class PopInstruction : public Instruction {
    public:
        PopInstruction(const string_t&s) : Instruction(s) 
        {
        }
        
        ~PopInstruction(){}

        std::error_code     execute(Context&ctx) const override
        {
            if(ctx.values.empty())
                return errors::empty_stack();
            ctx.values.pop();
            return {};
        }

        result_t   result() const override 
        { 
            return -1; 
        }
    };
    
    
    
    class ValueInstruction : public Instruction {
    public:
        ValueInstruction(const string_t& s, Any&& value) : Instruction(s), m_value(std::move(value))
        {
        }
        
        ~ValueInstruction(){}
        
        std::error_code     execute(Context&ctx) const override
        {
            ctx.values << m_value;
            return {};
        }

        result_t    result() const override 
        { 
            return &m_value.type(); 
        }

    private:
        Any m_value;
    };
    

    class VirtualMachine : public Instruction {
    public:
        std::vector<InstructionCPtr>    m_instructions;
        result_t                        m_result;
    
        VirtualMachine() : Instruction({})
        {
        }

        std::error_code     execute(Context&ctx) const override
        {
            for(auto& ins : m_instructions){
                if(!ins)
                    continue;
                std::error_code ec = ins->execute(ctx);
                if(ec)
                    return ec;
            }
            return {};
        }
        
        result_t    result() const override 
        { 
            return m_result; 
        }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // Table of known operators (this *WILL* grow)
    const OpData             Repo::kStandardOperators[] = {
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

    Repo& Repo::instance()
    {   
        static Repo *s_repo = new Repo;
        return *s_repo;
    }
    
    Repo::Repo() : CompoundInfo("yq::expr::Repo", std::source_location::current())
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
    
    Repo::~Repo()
    {
    }
    
    void    Repo::sweep_impl()
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
    
    Expect<Any>     Repo::constant(std::string_view k) const
    {
        std::u32string  k32 = to_u32string(k);
        return constant(k32);
    }
    
    Expect<Any>     Repo::constant(std::u32string_view k) const
    {
        auto i = m_constants.find(std::u32string(k));
        if(i != m_constants.end())
            return i->second;
        return errors::bad_argument();
    }

    bool            Repo::has_constant(std::string_view k) const
    {
        std::u32string  k32 = to_u32string(k);
        return has_constant(k32);
    }
    
    bool            Repo::has_constant(std::u32string_view k) const
    {
        return m_constants.contains(std::u32string(k));
    }

    bool            Repo::has_function(std::string_view k) const
    {
        return m_functions.lut.contains(k);
    }
    
    bool            Repo::has_function(std::u32string_view k) const
    {
        return m_functions.lut32.contains(k);
    }

    bool            Repo::has_operator(std::string_view k) const
    {
        std::u32string  k32 = to_u32string(k);
        return m_operators.contains(k32);
    }

    bool            Repo::has_operator(std::u32string_view k) const
    {
        return m_operators.contains(k);
    }
    
    bool            Repo::has_variable(std::string_view k) const
    {
        return m_variables.lut.contains(k);
    }
    
    bool            Repo::has_variable(std::u32string_view k) const
    {
        return m_variables.lut32.contains(k);
    }

    bool            Repo::is_punct_text(char32_t ch) const
    {
        return m_punctText.contains(ch);
    }

	const OpData*	Repo::operator_(std::u32string_view k) const
	{
		auto itr = m_operators.find(k);
		if(itr != m_operators.end())
			return (itr->second);
		return nullptr;
	}

    Expect<Any>     Repo::variable(std::string_view k) const
    {
        auto i = m_variables.lut.find(k);
        if(i != m_variables.lut.end() && i->second)
            return i->second->get(nullptr);
        return errors::bad_argument();
    }
    
    Expect<Any>     Repo::variable(std::u32string_view k) const
    {
        auto i = m_variables.lut32.find(k);
        if(i != m_variables.lut32.end() && i->second)
            return i->second->get(nullptr);
        return errors::bad_argument();
    }
    

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Repo&   repo() 
    {   
        return Repo::instance();
    }

//------------------------------------------------------------------------------
//  Tokenization

    Token   token(std::u32string_view in)
    {
        static const Repo& _r = repo();
        
        Token         ret{};
        if(in.empty())
            return ret;
            
        size_t&     cnt = ret.length;
        char32_t    ch  = in[0];
        
        //  white space
        if(is_space(ch)){
            ret.category	= SymCategory::Space;
            ret.kind		= SymKind::None;
            for(cnt = 1; cnt<in.size(); ++cnt){
                if(!is_space(in[cnt]))
                    break;
            }
            return ret;
        }
        
        //  text identifier
        if(is_alpha(ch) || (_r.punctuation_can_start_text() && _r.is_punct_text(ch))){
            ret.category	= SymCategory::Text;
            ret.kind		= SymKind::None;
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
                ret.category	= SymCategory::Value;
                ret.kind		= SymKind::Hexadecimal;
                //  it's a hex constant
                for(cnt=2; cnt<in.size(); ++cnt){
                    if(!is_xdigit(in[cnt]))
                        break;
                }
                return ret;
            }
            
            if((ch == '0') && is_digit(nx)){
                ret.category	= SymCategory::Value;
                ret.kind		= SymKind::Octal;
                
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
                ret.category	= SymCategory::Value;
                ret.kind		= SymKind::Float;
            } else {
                ret.category	= SymCategory::Value;
                ret.kind		= SymKind::Integer;
            }
            
            return ret;
        }   // end of value test
        
        
        if(is_punct(ch)){
            ret.category	= SymCategory::Operator;
            
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
        
        return Token{ .category=SymCategory::Error, .length=1 };
    }


    Expect<UserExpr::SymVector>   tokenize(std::string_view input)
    {
        std::u32string  u32 = to_u32string(input);
        return tokenize(u32);
    }
    
    Expect<UserExpr::SymVector>   tokenize(std::u32string_view input)
    {
        SymVector   ret;
        std::error_code ec  = tokenize(input, ret);
        if(ec != std::error_code())
            return unexpected(ec);
        return ret;
    }

    std::error_code  tokenize(std::u32string_view input, SymVector& tokens)
    {
        return tokenize(input, [&](SymCode c, std::u32string_view s) -> std::error_code {
            tokens.push_back(Symbol{ 
                    .text = std::u32string(s),
					.category = c.category,
					.kind = c.kind
				});
            return std::error_code();
        });
    }
    
    std::error_code  tokenize(std::string_view input, SymVector& tokens)
    {
        std::u32string  u32 = to_u32string(input);
        return tokenize(u32, tokens);
    }
        
    std::error_code  tokenize(std::u32string_view input, TokenFN&&fn)
    {
        if(!fn){
            return errors::bad_argument();
        }
        
        for(std::u32string_view i=input; !i.empty(); ){
            Token   t   = token(i);
            if((t.category == SymCategory::Error) || (t.length == 0)){
                return errors::bad_argument();
            }
            
            fn({.category=t.category, .kind = t.kind}, i.substr(0, t.length));
            i = i.substr(t.length);
        }
        return std::error_code();
    }
    
    std::error_code  tokenize(std::string_view input, TokenFN&& fn)
    {
        std::u32string      u32 = to_u32string(input);
        return tokenize(u32, std::move(fn));
    }

//------------------------------------------------------------------------------
//  Streamlining (static user-expr)


    std::error_code      s_constants(SymVector&syms)
    {
        static const Repo& _r = repo();
        for(Symbol& sym : syms){
            if(sym.category != SymCategory::Text)
                continue;
            if(sym.kind != Symbol::Kind::None)
                continue;
            if(_r.has_constant(sym.text)){
                sym.kind    = SymKind::Constant;
            } else {
                sym.kind    = SymKind::Variable;
            }
        }
        return {};
    }

    std::error_code s_functions(SymVector&syms)
    {
        Symbol* last    = nullptr;
		for(auto itr = syms.begin(); itr != syms.end(); last=&*itr, ++itr){
            if( itr -> category != SymCategory::Open)
                continue;
            if(!last)
                continue;
            if(last -> category != SymCategory::Text)
                continue;

            switch(itr->kind){
            case SymKind::Generic:
                last -> kind = SymKind::Function;
                break;
                
            //  folding it into the function
            //case SymKind::Tuple:
                //last -> kind = SymKind::Constructor;
                //break;
            default:
                break;
            }
		}
        return {};
    }

    std::error_code s_open_close(SymVector&syms)
    {
		for(Symbol& sym : syms){
			if(sym.text == U","){
				sym.category	= SymCategory::Special;
				sym.kind		= SymKind::Comma;
			}
			if(sym.text == U"("){
				sym.category	= SymCategory::Open;
				sym.kind		= SymKind::Generic;
			}
			if(sym.text == U")"){
				sym.category	= SymCategory::Close;
				sym.kind		= SymKind::Generic;
			}
			if(sym.text == U"["){
				sym.category	= SymCategory::Open;
				sym.kind		= SymKind::Array;
			}
			if(sym.text == U"]"){
				sym.category	= SymCategory::Close;
				sym.kind		= SymKind::Array;
			}
			if(sym.text == U"{"){
				sym.category	= SymCategory::Open;
				sym.kind		= SymKind::Tuple;
			}
			if(sym.text == U"}"){
				sym.category	= SymCategory::Close;
				sym.kind		= SymKind::Tuple;
			}
		}
        return {};
    }
    

    std::error_code s_operators(SymVector&syms)
    {
        static const Repo& _r = repo();
		SymCode		last	= {};
		for(auto itr = syms.begin(); itr != syms.end(); last=*itr, ++itr){
			if( itr -> category != SymCategory::Operator)
				continue;
			if( itr -> kind != SymKind::None)
				continue;
			const OpData* op = _r.operator_(itr->text);
			if(!op)
				return errors::bad_argument();
			
			itr->category	= op->category;
			itr->kind		= op->kind;
			itr->priority  	= op->priority;
            itr->argcnt     = op->args;
		}
        return {};
    }
    
    
    std::error_code s_signs(SymVector&syms)
    {
		SymCode		last	= {};
		for(auto itr = syms.begin(); itr != syms.end(); last=*itr, ++itr){
			if((itr -> text != U"-") && (itr->text != U"+"))
				continue;
			// This symbol is "-" negative
			if(!expr::is_starting_term(last))
				continue;
			auto jtr = itr + 1;
			if(jtr == syms.end())
				continue;
			if(jtr -> category != SymCategory::Value)
				continue;
			if(!((jtr -> kind == SymKind::Integer) ||  (jtr -> kind == SymKind::Float))){
                if(itr->text == U"-"){
                    jtr -> kind = SymKind::Negate;
                    jtr -> text = U"negate";
                } else {
                    jtr -> kind = SymKind::Affirm;
                    jtr -> text = U"affirm";
                }
				continue;
			}
			
			jtr -> text	= itr->text + jtr->text;
			itr = syms.erase(itr);
		}
        return {};
    }

    std::error_code s_values(SymVector&syms)
    {
		for(Symbol& sym : syms) {
			if(sym.category != SymCategory::Value)
				continue;
			switch(sym.kind){
			case SymKind::Integer:
				sym.value	= Any((double) *to_int64(sym.text));
				break;
			case SymKind::Hexadecimal:
				sym.value	= Any((double) *to_hex64(sym.text.substr(2)));
				break;
			case SymKind::Float:
				sym.value	= Any((double) *to_double(sym.text));
				break;
			case SymKind::Octal:
				sym.value	= Any((double) *to_octal64(sym.text));
				break;
			default:
				break;
			}
		}
        return {};
    }


    std::error_code  streamline(SymVector& syms)
    {
        std::error_code ec;
        
        ec = s_open_close(syms);
        if(ec != std::error_code())
            return ec;

        ec = s_signs(syms);
        if(ec != std::error_code())
            return ec;

        ec = s_operators(syms);
        if(ec != std::error_code())
            return ec;

        ec = s_values(syms);
        if(ec != std::error_code())
            return ec;

        ec = s_functions(syms);
        if(ec != std::error_code())
            return ec;

        ec = s_constants(syms);
        if(ec != std::error_code())
            return ec;

        return {};
    }

//------------------------------------------------------------------------------
//  Algebra to RPN

    Expect<InstructionCPtr> compile(const SymVector&syms, const Context&ctx, Analysis* pAnalysis)
    {
        Ref<VirtualMachine>    ret = new VirtualMachine;
        
        return ret;
        return errors::todo();
    }
    


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    template <typename S>   void stream_out(S& out, const Symbol& sym)
    {
        out << "{" << key(sym.category) << "/" << key(sym.kind) << ": " << sym.text << "}";
    }

    log4cpp::CategoryStream&    operator<<(log4cpp::CategoryStream&out, const Symbol&sym)
    {
        stream_out(out, sym);
        return out;
    }
    
    std::ostream&    operator<<(std::ostream& out, const Symbol& sym)
    {
        stream_out(out, sym);
        return out;
    }

    template <typename S>   void stream_out(S& out, const SymVector& syms)
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
    }

    log4cpp::CategoryStream&    operator<<(log4cpp::CategoryStream&out, const SymVector&syms)
    {
        stream_out(out, syms);
        return out;
    }
    

    std::ostream&    operator<<(std::ostream&out, const SymVector&syms)
    {
        stream_out(out, syms);
        return out;
    }
    
    template <typename S> void stream_out(S&out, const Token& tok)
    {
        out << "{" << key(tok.category) << "/" << key(tok.kind) << ": " << tok.length << "}";
    }

    log4cpp::CategoryStream&    operator<<(log4cpp::CategoryStream& out, const Token& tok)
    {
        stream_out(out, tok);
        return out;
    }

    std::ostream&    operator<<(std::ostream&out, const Token&tok)
    {
        stream_out(out, tok);
        return out;
    }
    

}


namespace yq {



//------------------------------------------------------------------------------
//  Algebra to RPN

    struct UserExpr::SymData : public Symbol {
        bool        has_value   = false;
        
        SymData() {}
        SymData(const Symbol& sym) : Symbol(sym) {}
    };

    std::error_code	UserExpr::algebra_to_rpn(SymVector& rpn, const SymVector& alg)
    {
        SymDataStack    pending;
        SymData         lastPoppedOpen = {};
        SymData*        sd  = nullptr;
        
        for(const Symbol& sym : alg){
            switch(sym.category){
            case Symbol::Category::None:
                //  ignore
                break;
            case Symbol::Category::Error:
                return errors::bad_userexpr();
            case Symbol::Category::Operator:
                while(!pending.empty()){
                    const Symbol& top   = pending.top();
                    if(top.category == Symbol::Category::Open)
                        break;
                    if((top.category == Symbol::Category::Operator) && (top.priority < sym.priority))
                        break;
                    rpn.push_back(pending.pop());
                }
                pending << sym;
                break;
            case Symbol::Category::Space:
                //  ignore 
                break;
            case Symbol::Category::Text:
                a2r_decl_value(pending);
                switch(sym.kind){
                case Symbol::Kind::Constant:
                    rpn.push_back(sym);
                    break;
                case Symbol::Kind::Constructor:
                    rpn.push_back(sym);
                    break;
                case Symbol::Kind::Function:
                    pending << sym;
                    break;
                case Symbol::Kind::Variable:
                    pending << sym;
                    break;
                default:
                    return errors::bad_userexpr();
                }
                break;
            case Symbol::Category::Value:
                a2r_decl_value(pending);
                rpn.push_back(sym);
                break;
            case Symbol::Category::Open:
                pending << sym;
                break;
            case Symbol::Category::Close:
                lastPoppedOpen.category = {};
				while(!pending.empty()){
                    auto& top   = pending.top();
                    
                    if(top.category == Symbol::Category::Open){
                        if(top.kind != sym.kind){
                            return errors::bad_userexpr();
                        }
                        lastPoppedOpen = pending.pop();
                        break;
                    }
                    
                    rpn.push_back(pending.pop());
				}
                if(!lastPoppedOpen.category)
                    return errors::bad_userexpr();
                if(lastPoppedOpen.argcnt){  // slight hack
                    sd      = pending.peek(0);
                    if(sd && (sd->category == Symbol::Category::Text) &&
                        ((sd->kind == Symbol::Kind::Constructor) || (sd->kind == Symbol::Kind::Function)))
                    {
                        sd -> argcnt = lastPoppedOpen.argcnt;
                    }
                    a2r_decl_value(pending);
                }
                break;
            case Symbol::Category::Special:
                switch(sym.kind){
                case Symbol::Kind::Comma:
                    
                    sd  = a2r_top_open(pending);
                    if(!sd)
                        return errors::bad_userexpr();
                    if(!sd->has_value)
                        return errors::bad_userexpr();
                    sd->has_value   = false;;
                    break;
                default:
                    return errors::todo();
                }
            }
        }
        
        while(!pending.empty()){
            Symbol  s   = pending.pop();
            if(s.category != Symbol::Category::Operator){
                return errors::bad_userexpr();
            }
            rpn.push_back(s);
        }
        
        if(pending.empty())
            return {};
        
        return errors::bad_userexpr();
    }

    UserExpr::SymData*   UserExpr::a2r_top_open(SymDataStack& stack)
    {
        for(auto itr = stack.rbegin(); itr != stack.rend(); ++itr){
            if(itr->category == Symbol::Category::Open)
                return &*itr;
        }
        return nullptr;
    }

    void                 UserExpr::a2r_decl_value(SymDataStack&stack)
    {
        SymData*     sym = a2r_top_open(stack);
        if(!sym)
            return;
        if(sym->has_value)
            return;
        sym->has_value  = true;
        ++(sym->argcnt);
    }

//------------------------------------------------------------------------------
//  Execution

    Expect<Any>  UserExpr::execute(u32string_any_map_t&vars, const SymVector& codes)
    {
        std::error_code ec;
        any_stack_t     theStack;
        for(const Symbol& sym : codes){
            switch(sym.category){
            case Symbol::Category::None:
                //  ignore
                break;
            case Symbol::Category::Error:
                return errors::bad_instruction();
            case Symbol::Category::Operator:
                ec  = x_operator(theStack, sym);
                if(ec != std::error_code())
                    return unexpected(ec);
                break;
            case Symbol::Category::Space:
                //  ignore
                break;
            case Symbol::Category::Text:
                ec = x_text(theStack, vars, sym);
                if(ec != std::error_code())
                    return unexpected(ec);
                break;
            case Symbol::Category::Value:
                ec = x_value(theStack, sym);
                if(ec != std::error_code())
                    return unexpected(ec);
                break;
            case Symbol::Category::Open:
                return errors::todo();
            case Symbol::Category::Close:
                return errors::todo();
            case Symbol::Category::Special:
                ec = x_special(theStack, vars, sym);
                if(ec != std::error_code())
                    return unexpected(ec);
                break;
            }
        }

        if(theStack.empty())
            return errors::empty_stack();
        if(theStack.size() > 1)
            return errors::mulitple_values();
        return theStack.pop();
    }
    
    std::error_code      UserExpr::x_assign(any_stack_t& values, u32string_any_map_t&vars, const Symbol&sym)
    {
        if(values.empty())
            return errors::empty_stack();
        if(sym.text.empty())
            return errors::empty_key();
        vars[sym.text]  = values.pop();
        return {};
    }



    std::error_code      UserExpr::x_constant(any_stack_t&values, const Symbol&sym)
    {   
        static const expr::Repo& _r = expr::repo();
        auto x = _r.constant(sym.text);
        if(x){
            values.push_back(*x);
            return {};
        }
        return x.error();
    }

    std::error_code      UserExpr::x_constructor(any_stack_t& values, const Symbol&sym)
    {
        if(values.size() < sym.argcnt)
            return errors::empty_stack();

        const ConstructorInfo*  ci = x_constructor_find(values, sym);
        if(!ci)
            return errors::bad_constructor();
        
        Expect<Any> ret = ci->invoke(values.top_cspan(sym.argcnt));
        if(!ret)
            return ret.error();
        values << *ret;
        return {};
    }

    const ConstructorInfo*   UserExpr::x_constructor_find(any_stack_t&, const Symbol&)
    {
        return nullptr;
    }

    std::error_code      UserExpr::x_function(any_stack_t& values, const Symbol& sym)
    {
        if(values.size() < sym.argcnt)
            return errors::empty_stack();
            
        switch(sym.argcnt){
        case 0:
            return x_function_zero(values, sym);
        case 1:
            return x_function_one(values, sym);
        default:
            return x_function_more(values, sym);
        }


#if 0
    /*
    
        Functions....
        
        *)  Actual Functions (Type -- first arg, Globals, Repo)

        *)  Methods on Type (first arg)

        *)  Properties (getters)
        
            For instance, geodetic & latitude,
            
                latitude(geo)
        
        *)  Construction
        
            degree(20)
            vec2d(x,y)
            
        *)  Conversions
        
        
        
    */



        const MethodInfo*   mi  = x_function_find(values, sym);
        if(!mi)
            return errors::bad_function();
        
        Expect<Any>     ret;
        if(mi->is_static()){
            ret     = mi -> invoke(values.top_cspan(sym.argcnt));
        } else if(!mi->is_const()){
            return errors::bad_function();
        } else {
            if(!sym.argcnt)
                return errors::bad_function();
                
        }
#endif
    }

    std::error_code  UserExpr::x_function_zero(any_stack_t&, const Symbol&)
    {
        const expr::Repo& _repo   = expr::repo();
        
        
        return create_error<"zero-arg functions are not yet implemented">();
    }
    
    std::error_code  UserExpr::x_function_one(any_stack_t&, const Symbol&)
    {
        return create_error<"one-arg functions are not yet implemented">();
    }
    
    std::error_code  UserExpr::x_function_more(any_stack_t&, const Symbol&)
    {
        return create_error<"more-arg functions are not yet implemented">();
    }

    const MethodInfo*    UserExpr::x_function_find(any_stack_t&, const Symbol&)
    {
        return nullptr;
    }

    std::error_code  UserExpr::x_operator(any_stack_t& values, const Symbol& symbol)
    {
        if(!symbol.argcnt)
            return errors::bad_operator();
        
        std::span<const Any>  args = values.top_cspan(symbol.argcnt);
        if(args.size() < symbol.argcnt){
            return errors::insufficient_arguments();
        }
        
        const OperatorInfo* op  = x_operator_find(args, (Operator) symbol.kind);
        if(!op)
            return errors::bad_operator();
        
        Expect<Any>     res = op->invoke(args);
        if(!res)
            return res.error();
            
        values.pop_last(symbol.argcnt);
        values << std::move(*res);
        return {};
    }

    const OperatorInfo*  UserExpr::x_operator_find(std::span<const Any> span, Operator opCode)
    {
        if(span.size() == 0)
            return nullptr;
            
        const OperatorInfo* best    = nullptr;
        int                 score   = 0;
        
        const TypeInfo& ti  = span[0].type();
        auto er             = ti.operators(opCode);
        for(auto itr=er.first; itr != er.second; ++itr){
            const OperatorInfo* op  = itr->second;
            if(!op)
                continue;
                
            int     r   = op -> type_match(span);
            if(r < 0)
                continue;
            if(r == 0)
                return op;

            if((r<score) || !best){
                best        = op;
                score       = r;
            }
        }
        
        return best;
    }
    
    std::error_code      UserExpr::x_special(any_stack_t&values, u32string_any_map_t&vars, const Symbol&sym)
    {   
        switch(sym.kind){
        case Symbol::Kind::Assign:
            return x_assign(values, vars, sym);
        case Symbol::Kind::Duplicate:
            if(values.empty())
                return errors::empty_stack();
            values << values.top();
            return {};
        default:
            return errors::bad_instruction();
        }
    }

    std::error_code      UserExpr::x_text(any_stack_t&values, const u32string_any_map_t&vars, const Symbol&sym)
    {
        switch(sym.kind){
        case Symbol::Kind::Function:
            return x_function(values, sym);
        case Symbol::Kind::Constructor:
            return x_constructor(values, sym);
        case Symbol::Kind::Constant:
            return x_constant(values, sym);
        case Symbol::Kind::Variable:
            return x_variable(values, vars, sym);
        default:
            return errors::bad_instruction();
        }
    }
    
    std::error_code      UserExpr::x_value(any_stack_t&values, const Symbol&sym)
    {
        values << sym.value;
        return {};
    }

    std::error_code      UserExpr::x_variable(any_stack_t&values, const u32string_any_map_t&vars, const Symbol&sym)
    {   
        auto i = vars.find(sym.text);
        if(i == vars.end())
            return errors::bad_variable();
        values << i->second;
        return {};
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
		ec	= expr::tokenize(uxpr, m_algebra);
		if(ec != std::error_code())
            return ec;
		
		ec	        = expr::streamline(m_algebra);
		if(ec != std::error_code())
            return ec;
        
        ec      = algebra_to_rpn(m_rpn, m_algebra);
		if(ec != std::error_code())
            return ec;
    
        return {};
	}

    Expect<Any>     UserExpr::evaluate() const
    {
        expr::Context     context;
        return evaluate(context);
    }

    Expect<Any>     UserExpr::evaluate(expr::Context&ctx) const
    {
        if(!is_good())
            return errors::bad_userexpr();
        return execute(ctx.variables, m_rpn);
    }


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
    namespace {
        YQ_INVOKE( expr::repo(); )
    }
}


