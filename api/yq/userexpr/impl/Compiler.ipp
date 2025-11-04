////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Compiler.hpp"

#include <yq/core/Any.hpp>

#include <yq/text/parse32.hpp>

#include <yq/userexpr/errors.hpp>
#include <yq/userexpr/Analysis.hpp>
#include <yq/userexpr/Context.hpp>

#include <yq/userexpr/impl/Instruction.hpp>
#include <yq/userexpr/impl/OpData.hpp>
#include <yq/userexpr/impl/Repo.hpp>
#include <yq/userexpr/impl/SymData.hpp>
#include <yq/userexpr/impl/Symbol.hpp>
#include <yq/userexpr/impl/VirtualMachine.hpp>

#include <yq/userexpr/opcode/AssignInstruction.hpp>
#include <yq/userexpr/opcode/ConstantInstruction.hpp>
#include <yq/userexpr/opcode/DuplicateInstruction.hpp>
#include <yq/userexpr/opcode/FunctionInstruction.hpp>
#include <yq/userexpr/opcode/NullInstruction.hpp>
#include <yq/userexpr/opcode/OperatorInstruction.hpp>
#include <yq/userexpr/opcode/PopInstruction.hpp>
#include <yq/userexpr/opcode/ValueInstruction.hpp>
#include <yq/userexpr/opcode/VariableInstruction.hpp>

namespace yq::expr {
    Compiler::Compiler(const Context& ctx, Analysis& rAnalysis, Ref<VirtualMachine> vm) : 
        m_context(ctx), 
        m_machine(vm), 
        m_analysis(rAnalysis)
    {
    }

    std::error_code     Compiler::add(const Symbol& sym)
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

    std::error_code     Compiler::add_assignment(const Symbol& sym)
    {
        m_pending << sym;
        return {};
    }
    
    std::error_code     Compiler::add_close(const Symbol& sym)
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
            SymData* sd      = m_pending.peek(1);
            if(sd && (sd->category == SymCategory::Text) &&
                ((sd->kind == SymKind::Constructor) || (sd->kind == SymKind::Function)))
            {
                sd -> argcnt = lastPop.argcnt;
            }
            decl_value();
        }

        return {};
    }

    std::error_code     Compiler::add_comma(const Symbol& sym)
    {
        SymData*sd  = opening();
        if(!sd)
            return create_error<"bad user expression (comma outside open/close)">();
        if(!sd->has_value)
            return create_error<"bad user expression (comma without a left-side value)">();
        sd->has_value   = false;;
        return {};
    }
    
    std::error_code     Compiler::add_constant(const Symbol& sym)
    {
        decl_value();
        return push(new ConstantInstruction(sym.text));
    }

    std::error_code     Compiler::add_constructor(const Symbol& sym)
    {
        m_pending << sym;
        return {};
    }

    std::error_code     Compiler::add_duplicate(const Symbol& sym)
    {
        m_pending << sym;
        return {};
    }

    std::error_code     Compiler::add_float(const Symbol& sym)
    {
        auto    val = to_double(sym.text);
        if(!val)
            return val.error();
        decl_value();
        return push(new ValueInstruction(sym.text, Any((double) *val)));
    }

    std::error_code     Compiler::add_function(const Symbol& sym)
    {
        SymData sd(sym);
        sd.sstack   = m_stack;
        m_pending << sd;
        return {};
    }

    std::error_code     Compiler::add_hexadecimal(const Symbol& sym)
    {
        auto    val = to_hex64(sym.text.substr(2));
        if(!val)
            return val.error();
        decl_value();
        return push(new ValueInstruction(sym.text, Any((double) *val)));
    }

    std::error_code     Compiler::add_integer(const Symbol& sym)
    {
        auto    val = to_int64(sym.text);
        if(!val)
            return val.error();
        decl_value();
        return push(new ValueInstruction(sym.text, Any((double) *val)));
    }

    std::error_code     Compiler::add_octal(const Symbol& sym)
    {
        auto    val = to_octal64(sym.text);
        if(!val)
            return val.error();
        decl_value();
        return push(new ValueInstruction(sym.text, Any((double) *val)));
    }

    std::error_code     Compiler::add_open(const Symbol& sym)
    {
        m_pending << sym;
        return {};
    }

    std::error_code     Compiler::add_operator(const Symbol& sym)
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

    std::error_code     Compiler::add_special(const Symbol& sym)
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

    std::error_code     Compiler::add_text(const Symbol& sym)
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
    
    std::error_code     Compiler::add_value(const Symbol& sym)
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
    
    std::error_code     Compiler::add_variable(const Symbol& sym)
    {
        decl_value();
        return push(new VariableInstruction(sym.text));
    }

    std::error_code     Compiler::compile(const SymVector& syms)
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
        
    void        Compiler::decl_value()
    {
        SymData*     sym = opening();
        if(!sym)
            return;
        if(sym->has_value)
            return;
        sym->has_value  = true;
        ++(sym->argcnt);
    }

    SymData*    Compiler::opening()
    {
        for(auto itr = m_pending.rbegin(); itr != m_pending.rend(); ++itr){
            if(itr->category == SymCategory::Open)
                return &*itr;
        }
        return nullptr;
    }
    
    std::error_code     Compiler::pop()
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

    std::error_code     Compiler::pop_assignment(const SymData&sym)
    {
        push(new AssignInstruction(sym.text));
        return {};
    }

    std::error_code     Compiler::pop_constructor(const SymData&)
    {
        return errors::todo();
    }

    std::error_code     Compiler::pop_duplicate(const SymData&sym)
    {
        return push(new DuplicateInstruction(sym.text));
    }

    std::error_code     Compiler::pop_function(const SymData& sd)
    {
        SymData sd2(sd);
        sd2.argcnt  = m_stack - sd.sstack;
        return push(new FunctionInstruction(sd2));
    }

    std::error_code     Compiler::pop_operator(const SymData& sym)
    {
        return push(new OperatorDynamic(sym));
    }

    std::error_code   Compiler::push(InstructionCPtr insptr)
    {
        if(insptr && m_machine){
            if(insptr->pop_count() > m_stack)
                return create_error<"bad user expression (stack collision anticipated)">();
            m_stack -= insptr->pop_count();
            m_stack += insptr->push_count();
            m_machine->m_instructions.push_back(insptr);
        }
        return {};
    }
}
