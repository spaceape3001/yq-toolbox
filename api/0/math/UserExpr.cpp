////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////



#include <0/math/expr/NullInstruction.hpp>
#include <0/math/expr/VirtualMachine.hpp>

#include <0/math/expr/SymData.hpp>

#include "expr/AssignInstruction.ipp"
#include "expr/ConstantInstruction.ipp"
#include "expr/DuplicateInstruction.ipp"
#include "expr/Instruction.ipp"
#include "expr/OperatorInstruction.ipp"
#include "expr/PopInstruction.ipp"
#include "expr/Repo.ipp"
#include "expr/Streamline.ipp"
#include "expr/Symbol.ipp"
#include "expr/Token.ipp"
#include "expr/Tokenize.ipp"
#include "expr/ValueInstruction.ipp"
#include "expr/VariableInstruction.ipp"
#include "expr/VirtualMachine.ipp"

#include "UserExprImpl.hpp"

#include <0/basic/errors.hpp>
#include <0/basic/DelayInit.hpp>
#include <0/basic/Stack.hpp>
#include <0/basic/TextUtils.hpp>
#include <0/basic/TextUtils32.hpp>
#include <0/math/expr/OpData.hpp>
#include <0/meta/ArgInfo.hpp>
#include <0/meta/ConstructorInfo.hpp>
#include <0/meta/GlobalInfo.hpp>
#include <0/meta/MethodInfo.hpp>
#include <0/meta/OperatorInfo.hpp>
#include <0/meta/TypeInfo.hpp>


namespace yq::expr {
    namespace {


        using conditional_t = std::variant<std::monostate, std::error_code>;

    }



    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    namespace {

        const MethodInfo*   is_zero_method(const MethodInfo* mi)
        {
            if(!mi->is_static())
                return nullptr;
            if(mi->arg_count() != 0)
                return nullptr;
            const ArgInfo*  res = mi->result();
            if(!res)
                return nullptr;
            auto& rtype = res->type();
            if(!rtype.is_type())
                return nullptr;
            return mi;
        }
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    
    


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
        const std::string   m_text8;
        const uint16_t      m_argcnt;

        FunctionDynamic(const SymData& sd) : Instruction(sd.text), m_text8(to_string(sd.text)), m_argcnt(sd.argcnt)
        {
        }
        
        #if 0
        
        conditional_t x_repo(any_stack_t&values) const 
        {
            static const Repo&          _r  = repo();
            auto  args  = values.top_cspan(m_argcnt);
            const MethodInfo*   call    = _r.all_functions(m_text, [&](const MethodInfo* mi) -> const MethodInfo* {
                if(mi.arg_count() != m_argcnt)
                    return;
                
            });
        }

        conditional_t x_global(any_stack_t&values) const 
        {
            static const GlobalInfo&    _g  = GlobalInfo::instance();
            auto  args  = values.top_cspan(m_argcnt);
        }
        #endif
        
        virtual std::error_code     execute(any_stack_t&values, Context&) const override
        {
        #if 0
            static const GlobalInfo&    _g  = GlobalInfo::instance();

            if(values.size() < m_argcnt)
                return errors::empty_stack();

            Any&    val = values.peek(m_argcnt-1);
            const TypeInfo& type    = val.type();
        #endif
            return errors::todo();
        }
    };

    class FunctionOneDynamic : public Instruction {
    public:

        const std::string   m_text8;

        FunctionOneDynamic(const SymData& sd) : Instruction(sd.text), m_text8(to_string(sd.text))
        {
        }
        
        #if 0
        std::pair<bool,std::error_code> x_repo(any_stack_t&) const 
        {
            static const Repo&          _r  = repo();
        }

        std::pair<bool,std::error_code> x_global(any_stack_t&) const 
        {
            static const GlobalInfo&    _g  = GlobalInfo::instance();
        }
        #endif

        virtual std::error_code     execute(any_stack_t&values, Context&) const override
        {
        #if 0
            static const Repo&          _r  = repo();

            if(values.empty())
                return errors::empty_stack();

            Any&    val = values.top();
            const TypeInfo& type    = val.type();
        #endif
        
            return errors::todo();
        }
    };
    
    
    class FunctionZeroMethodInfo : public Instruction {
    public:
        const MethodInfo*   m_method;
        const TypeInfo*     m_result = nullptr;
        
        FunctionZeroMethodInfo(const string_t& s, const MethodInfo* method) : Instruction(s), m_method(method)
        {
            const ArgInfo*  resinfo = m_method -> result();
            if(resinfo)
                m_result    = static_cast<const TypeInfo*>(&(resinfo->type()));
        }
        
        std::error_code     execute(any_stack_t&values, Context&) const override
        {
            auto val    = m_method -> invoke({});
            if(!val)
                return val.error();
            values.push_back(*val);
            return {};
        }
        
        result_t   result() const override 
        { 
            return m_result; 
        }
    };
    
    class FunctionZeroTypeInfo : public Instruction {
    public:
        const TypeInfo* m_type;
        
        FunctionZeroTypeInfo(const string_t& s, const TypeInfo* type) : Instruction(s), m_type(type)
        {
        }
    
        std::error_code     execute(any_stack_t&values, Context&) const override
        {
            values.push_back(Any(m_type));
            return {};
        }

        result_t   result() const override 
        { 
            return m_type; 
        }
    };
    

    




//------------------------------------------------------------------------------
//  Algebra to RPN
    
    struct Builder {
        const Context&                  m_context;
        Ref<VirtualMachine>             m_machine;
        Analysis&                       m_analysis;
        SymDataStack                    m_pending;
        Stack<const TypeInfo*>          m_types;
        
        Builder(const Context& ctx, Analysis& rAnalysis, Ref<VirtualMachine> vm) : 
            m_context(ctx), 
            m_machine(vm), 
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
            push(new ConstantInstruction(sym.text));
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
            push(new ValueInstruction(sym.text, Any((double) *val)));
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
            push(new ValueInstruction(sym.text, Any((double) *val)));
            return {};
        }

        std::error_code     add_integer(const Symbol& sym)
        {
            auto    val = to_int64(sym.text);
            if(!val)
                return val.error();
            decl_value();
            push(new ValueInstruction(sym.text, Any((double) *val)));
            return {};
        }

        std::error_code     add_octal(const Symbol& sym)
        {
            auto    val = to_octal64(sym.text);
            if(!val)
                return val.error();
            decl_value();
            push(new ValueInstruction(sym.text, Any((double) *val)));
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
            push(new VariableInstruction(sym.text));
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
            push(new AssignInstruction(sym.text));
            return {};
        }

        std::error_code     pop_constructor(const SymData&)
        {
            return errors::todo();
        }

        std::error_code     pop_duplicate(const SymData&sym)
        {
            push(new DuplicateInstruction(sym.text));
            return {};
        }

        std::error_code     pop_function(const SymData& sd)
        {
            switch(sd.argcnt){
            case 0:
                return pop_function_zero(sd);
            case 1:
                return pop_function_one(sd);
            default:
                return pop_function_many(sd);
            }
            return {};
        }

        std::error_code     pop_function_many(const SymData& sd)
        {
            push(new FunctionDynamic(sd));
            return {};
        }
        
        std::error_code     pop_function_one(const SymData& sd)
        {
            push(new FunctionOneDynamic(sd));
            return {};
        }
        
        std::error_code     pop_function_zero(const SymData& sd)
        {
            static const Repo&          _r  = repo();
            static const GlobalInfo&    _g  = GlobalInfo::instance();
            
            
            //  Call on methods
            const MethodInfo* call = _r.all_functions(sd.text, is_zero_method);
            if(call){
                push(new FunctionZeroMethodInfo(sd.text, call));
                return {};
            }

            std::string txt8    = to_string(sd.text);

            call = _g.all_functions(txt8, is_zero_method);
            if(call){
                push(new FunctionZeroMethodInfo(sd.text, call));
                return {};
            }

            const TypeInfo* type    = TypeInfo::find(txt8);
            if(type){
                push(new FunctionZeroTypeInfo(sd.text, type));
                return {};
            }
            
            return errors::bad_function();
        }
        

        std::error_code     pop_operator(const SymData& sym)
        {
            push(new OperatorDynamic(sym));
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
        
        void    push(InstructionCPtr insptr)
        {
            if(insptr && m_machine)
                m_machine->m_instructions.push_back(insptr);
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
    


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    
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
        
        Ref<expr::VirtualMachine> vm  = new expr::VirtualMachine;
        
        expr::Builder         builder(ctx, analy, vm);
        ec      = builder.compile(m_algebra);
        if(ec)
            return ec;
        m_machine       = vm;
        return {};
	}

    Expect<Any>     UserExpr::evaluate() const
    {
        expr::Context     context;
        return evaluate(context);
    }

    Expect<Any>     UserExpr::evaluate(expr::Context&ctx) const
    {
        if(!m_machine.valid())
            return errors::bad_userexpr();

        any_stack_t             values;
        std::error_code ec  =  m_machine -> execute(values, ctx);
        if(ec != std::error_code())
            return unexpected(ec);
        if(values.empty())
            return errors::empty_stack();
        if(values.size() > 1)
            return errors::mulitple_values();
        return values.pop();
    }
}


