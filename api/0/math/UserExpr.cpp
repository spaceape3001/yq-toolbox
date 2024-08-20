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

    struct SymData : public Symbol {
        bool            has_value   = false;
		uint16_t        priority	= 0;
        uint16_t        argcnt      = 0;
        
        SymData() {}
        SymData(const Symbol& sym) : Symbol(sym) {}
    };

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

    const OperatorInfo*     find_operator(std::span<const Any> span, Operator opCode)
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
    

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    class AssignInstruction : public Instruction {
    public:
        AssignInstruction(const string_t& s) : Instruction(s)
        {
        }
        
        ~AssignInstruction(){}
        
        std::error_code     execute(any_stack_t&values, Context& ctx) const override
        {
            if(values.empty()){
                return errors::empty_stack();
            }
            
            ctx.variables[m_text]  = values.pop();
            return {};
        }

        result_t    result() const override
        {
            return -1;
        }
    };
    
    class ConstantInstruction : public Instruction {
    public:
        ConstantInstruction(const string_t& s) : Instruction(s)
        {
        }
        
        ~ConstantInstruction()
        {
        }

        virtual std::error_code     execute(any_stack_t&values, Context&) const override
        {
            static const Repo& _repo    = repo();
            auto x  = _repo.constant(m_text);
            if(!x)
                return x.error();
            values << *x;
            return {};
        }
    };
    
    class DuplicateInstruction : public Instruction {
    public:
        DuplicateInstruction(const string_t s) : Instruction(s)
        {
        }
        
        ~DuplicateInstruction(){}
        
        virtual std::error_code     execute(any_stack_t&values, Context&) const override
        {
            if(values.empty()){
                return errors::empty_stack();
            }
            
            values << values.top();
            return {};
        }
        
        result_t   result() const override 
        { 
            return 1; 
        }
    };

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

    class FunctionDynamic : public Instruction {
    public:
        FunctionDynamic(const SymData& sd) : Instruction(sd.text)
        {
        }
        
        virtual std::error_code     execute(any_stack_t&values, Context&) const override
        {
            return errors::todo();
        }
    };

    class FunctionOneDynamic : public Instruction {
    public:
        FunctionOneDynamic(const SymData& sd) : Instruction(sd.text)
        {
        }
        
        virtual std::error_code     execute(any_stack_t&values, Context&) const override
        {
            return errors::todo();
        }
    };
    
    class FunctionZeroDynamic : public Instruction {
    public:
        FunctionZeroDynamic(const SymData& sd) : Instruction(sd.text)
        {
        }
        
        virtual std::error_code     execute(any_stack_t&values, Context&) const override
        {
            return errors::todo();
        }
    };

    class NullInstruction : public Instruction {
    public:
        NullInstruction(const string_t&s) : Instruction(s) 
        {
        }
        
        ~NullInstruction(){}
        
        std::error_code     execute(any_stack_t&, Context&) const override
        {
            return {};
        }

        result_t   result() const override 
        { 
            return 0; 
        }
    };
    
    /*! \brief Dynamic operator when argument types aren't known until runtime
    */
    class OperatorDynamic : public Instruction {
    public:
    
        OperatorDynamic(const SymData&sym) : 
            Instruction(sym.text), m_operator((Operator) sym.kind), m_args(sym.argcnt)
        {
        }
        
        std::error_code     execute(any_stack_t&values, Context&ctx) const override
        {
            if(!m_args)
                return create_error<"bad user expression (dynamic operator with no arguments)">();
            
            std::span<const Any>  args = values.top_cspan(m_args);
            if(args.size() < m_args){
                return errors::insufficient_arguments();
            }
        
            const OperatorInfo* op  = find_operator(args, m_operator);
            if(!op)
                return create_error<"bad user expression (unable to find operator)">();
        
            Expect<Any>     res = op->invoke(args);
            if(!res)
                return res.error();
            
            values.pop_last(m_args);
            values << std::move(*res);
            return {};
        }

        Operator        m_operator;
        unsigned int    m_args;
    };
    
    class PopInstruction : public Instruction {
    public:
        PopInstruction(const string_t&s) : Instruction(s) 
        {
        }
        
        ~PopInstruction(){}

        std::error_code     execute(any_stack_t&values, Context&) const override
        {
            if(values.empty())
                return errors::empty_stack();
            values.pop();
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
        
        std::error_code     execute(any_stack_t&values, Context&) const override
        {
            values << m_value;
            return {};
        }

        result_t    result() const override 
        { 
            return &m_value.type(); 
        }

    private:
        Any m_value;
    };
    
    class VariableInstruction : public Instruction {
    public:
        VariableInstruction(const string_t& s) : Instruction(s)
        {
        }
        
        ~VariableInstruction(){}

        std::error_code     execute(any_stack_t&values, Context&ctx) const override
        {
            auto i = ctx.variables.find(m_text);
            if(i == ctx.variables.end())
                return errors::bad_variable();
            values << i->second;
            return {};
        }
    };
    

    class VirtualMachine : public Instruction {
    public:
        std::vector<InstructionCPtr>    m_instructions;
        result_t                        m_result;
    
        VirtualMachine() : Instruction({})
        {
        }

        std::error_code     execute(any_stack_t&values, Context&ctx) const override
        {
            for(auto& ins : m_instructions){
                if(!ins)
                    continue;
                std::error_code ec = ins->execute(values, ctx);
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

			const OpData* op = _r.operator_(in.substr(0, lc));
			if(op){
                ret.category    = op->category;
                ret.kind        = op->kind;
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


    std::error_code  streamline(SymVector& syms)
    {
        std::error_code ec;

        ec = s_signs(syms);
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
    
    struct Builder {
        const Context&                  m_context;
        Ref<VirtualMachine>             m_machine;
        std::vector<InstructionCPtr>&   m_instructions;
        Analysis&                       m_analysis;
        SymDataStack                    m_pending;
        
        Builder(const Context& ctx, Analysis& rAnalysis) : 
            m_context(ctx), 
            m_machine(new VirtualMachine), 
            m_instructions(m_machine->m_instructions),
            m_analysis(rAnalysis)
        {
        }
        
        SymData*    opening()
        {
            for(auto itr = m_pending.rbegin(); itr != m_pending.rend(); ++itr){
                if(itr->category == SymCategory::Open)
                    return &*itr;
            }
            return nullptr;
        }
        
        void        decl_value()
        {
            SymData*     sym = opening();
            if(!sym)
                return;
            if(sym->has_value)
                return;
            sym->has_value  = true;
            ++(sym->argcnt);
        }
        
        std::error_code     add_assignment(const Symbol& sym)
        {
            m_pending << sym;
            return {};
        }
        
        std::error_code     add_close(const Symbol& sym)
        {
            SymData lastPop{};

            while(!m_pending.empty()){
                auto& top = m_pending.top();
                
                if(top.category == SymCategory::Open){
                    if(top.kind != sym.kind)
                        return create_error<"bad user expression (mismatched opener)">();
                    lastPop = m_pending.pop();
                    break;
                }
                
                pop();
            }

            if(!lastPop.category)
                return create_error<"bad user expression (no opener)">();

            if(lastPop.argcnt){  // slight hack
                SymData* sd      = m_pending.peek(0);
                if(sd && (sd->category == SymCategory::Text) &&
                    ((sd->kind == SymKind::Constructor) || (sd->kind == SymKind::Function)))
                {
                    sd -> argcnt = lastPop.argcnt;
                }
                decl_value();
            }

            return {};
        }

        std::error_code     add_comma(const Symbol& sym)
        {
            SymData*sd  = opening();
            if(!sd)
                return create_error<"bad user expression (comma outside open/close)">();
            if(!sd->has_value)
                return create_error<"bad user expression (comma without a left-side value)">();
            sd->has_value   = false;;
            return {};
        }
        
        std::error_code     add_constant(const Symbol& sym)
        {
            decl_value();
            m_instructions.push_back(new ConstantInstruction(sym.text));
            return {};
        }

        std::error_code     add_constructor(const Symbol& sym)
        {
            m_pending << sym;
            return {};
        }

        std::error_code     add_duplicate(const Symbol& sym)
        {
            m_pending << sym;
            return {};
        }

        std::error_code     add_float(const Symbol& sym)
        {
            auto    val = to_double(sym.text);
            if(!val)
                return val.error();
            decl_value();
            m_instructions.push_back(new ValueInstruction(sym.text, Any((double) *val)));
            return {};
        }

        std::error_code     add_function(const Symbol& sym)
        {
            m_pending << sym;
            return {};
        }

        std::error_code     add_hexadecimal(const Symbol& sym)
        {
            auto    val = to_hex64(sym.text.substr(2));
            if(!val)
                return val.error();
            decl_value();
            m_instructions.push_back(new ValueInstruction(sym.text, Any((double) *val)));
            return {};
        }

        std::error_code     add_integer(const Symbol& sym)
        {
            auto    val = to_int64(sym.text);
            if(!val)
                return val.error();
            decl_value();
            m_instructions.push_back(new ValueInstruction(sym.text, Any((double) *val)));
            return {};
        }

        std::error_code     add_octal(const Symbol& sym)
        {
            auto    val = to_octal64(sym.text);
            if(!val)
                return val.error();
            decl_value();
            m_instructions.push_back(new ValueInstruction(sym.text, Any((double) *val)));
            return {};
        }

        std::error_code     add_open(const Symbol& sym)
        {
            m_pending << sym;
            return {};
        }

        std::error_code     add_operator(const Symbol& sym)
        {
            static const Repo&  _repo   = repo();
            const OpData*   op  = _repo.operator_(sym.text);
            if(!op)
                return create_error<"bad user expression (unable to find operator--in add_operator)">();
            
            SymData     sd(sym);
            sd.priority = op->priority;
            sd.argcnt   = op->args;
        
            while(!m_pending.empty()){
                const SymData& top   = m_pending.top();
                if(top.category == SymCategory::Open)
                    break;
                if((top.category == SymCategory::Operator) && (top.priority < sd.priority))
                    break;
                pop();
            }
            m_pending << sd;
            return {};
        }

        std::error_code     add_special(const Symbol& sym)
        {
            switch(sym.kind){
            case SymKind::Comma:
                return add_comma(sym);
            case SymKind::Assign:
                return add_assignment(sym);
            case SymKind::Duplicate:
                return add_duplicate(sym);
            default:
                return create_error<"bad user expression (unrecognized special symbol)">();
            }
        }

        std::error_code     add_text(const Symbol& sym)
        {
            switch(sym.kind){
            case SymKind::Constant:
                return add_constant(sym);
            case SymKind::Constructor:
                return add_constructor(sym);
            case SymKind::Function:
                return add_function(sym);
            case SymKind::Variable:
                return add_variable(sym);
            default:
                return create_error<"bad user expression (unrecognized text symbol)">();
            }
        }
        
        std::error_code     add_value(const Symbol& sym)
        {
            switch(sym.kind){
            case SymKind::Float:
                return add_float(sym);
            case SymKind::Hexadecimal:
                return add_hexadecimal(sym);
            case SymKind::Integer:
                return add_integer(sym);
            case SymKind::Octal:
                return add_octal(sym);
            default:
                return create_error<"bad user expression (unrecognized value symbol)">();
            }
        }
        
        std::error_code     add_variable(const Symbol& sym)
        {
            decl_value();
            m_instructions.push_back(new VariableInstruction(sym.text));
            return {};
        }
        
        std::error_code     pop()
        {
            if(m_pending.empty())
                return errors::empty_stack();
                
            SymData     sym = m_pending.pop();
            switch(sym.category){
            case SymCategory::Operator:
                return pop_operator(sym);
            case SymCategory::Text:
                switch(sym.kind){
                case SymKind::Constructor:
                    return pop_constructor(sym);
                case SymKind::Function:
                    return pop_function(sym);
                default:
                    break;
                }
                break;
            case SymCategory::Special:
                switch(sym.kind){
                case SymKind::Assign:
                    return pop_assignment(sym);
                case SymKind::Duplicate:
                    return pop_duplicate(sym);
                default:
                    break;
                }
                break;
            default:
                break;
            }
            return create_error<"bad user expression (unrecognized popped symbol)">();
        }

        std::error_code     pop_assignment(const SymData&sym)
        {
            m_instructions.push_back(new AssignInstruction(sym.text));
            return {};
        }

        std::error_code     pop_constructor(const SymData&)
        {
            return errors::todo();
        }

        std::error_code     pop_duplicate(const SymData&sym)
        {
            m_instructions.push_back(new DuplicateInstruction(sym.text));
            return {};
        }

        std::error_code     pop_function(const SymData& sd)
        {
            switch(sd.argcnt){
            case 0:
                m_instructions.push_back(new FunctionZeroDynamic(sd));
                break;
            case 1:
                m_instructions.push_back(new FunctionOneDynamic(sd));
                break;
            default:
                m_instructions.push_back(new FunctionDynamic(sd));
                break;
            }
            return {};
        }

        std::error_code     pop_operator(const SymData& sym)
        {
            m_instructions.push_back(new OperatorDynamic(sym));
            return {};
        }

        std::error_code     add(const Symbol& sym)
        {
            switch(sym.category){
            case SymCategory::None:
            case SymCategory::Space:
                //  ignore
                return {};
            case SymCategory::Error:
                return errors::bad_userexpr();
            case SymCategory::Operator:
                return add_operator(sym);
            case SymCategory::Value:
                return add_value(sym);
            case SymCategory::Text:
                return add_text(sym);
            case SymCategory::Open:
                return add_open(sym);
            case SymCategory::Close:
                return add_close(sym);
            case SymCategory::Special:
                return add_special(sym);
            default:
                return create_error<"bad user expression (unrecognized symbol)">();
            }
        }
        
        std::error_code     compile(const SymVector& syms)
        {
            std::error_code ec;
            add_open(Symbol{ .category=SymCategory::Open, .kind=SymKind::Guard });
            for(const Symbol& sym : syms){
                ec  = add(sym);
                if(ec != std::error_code())
                    return ec;
            }
            ec = add_close(Symbol{ .category=SymCategory::Close, .kind=SymKind::Guard });
            if(ec != std::error_code())
                return ec;
            return {};
        }
    };
    
    Expect<InstructionCPtr> compile(const SymVector&syms, const Context&ctx, Analysis& rAnalysis)
    {
        Builder         builder(ctx, rAnalysis);
        
        std::error_code ec  = builder.compile(syms);
        if(ec != std::error_code())
            return unexpected(ec);
        return builder.m_machine;
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
//  Execution

#if 0
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


    std::error_code      UserExpr::x_function(any_stack_t& values, const Symbol& sym)
    {
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
    }

#endif



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
        
        expr::Context ctx;
        expr::Analysis    analy;
        
        auto x  = expr::compile(m_algebra, ctx, analy);
        if(!x)
            return x.error();
        
        m_instruction   = *x;
        return {};
	}

    Expect<Any>     UserExpr::evaluate() const
    {
        expr::Context     context;
        return evaluate(context);
    }

    Expect<Any>     UserExpr::evaluate(expr::Context&ctx) const
    {
        if(!m_instruction.valid())
            return errors::bad_userexpr();

        any_stack_t             values;
        std::error_code ec  =  m_instruction -> execute(values, ctx);
        if(ec != std::error_code())
            return unexpected(ec);
        if(values.empty())
            return errors::empty_stack();
        if(values.size() > 1)
            return errors::mulitple_values();
        return values.pop();
    }


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
    namespace {
        YQ_INVOKE( expr::repo(); )
    }
}


