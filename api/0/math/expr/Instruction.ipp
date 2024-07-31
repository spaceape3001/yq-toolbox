////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Instruction.hpp"
#include "Symbol.hpp"
//#include "Repo.hpp"
#include <0/basic/Logging.hpp>
#include <0/basic/TextUtils32.hpp>
#include <0/basic/Stack.hpp>

namespace yq::expr {
    enum class InsType {
        None,
        Open,
        Close,
        Operator,
        Function
    };

    struct InsInfo {
        InsType                 type        = InsType::None;
        std::u32string_view     text, other;
        uint16_t                commas      = 0;
        uint16_t                values      = 0;
        int8_t                  priority    = 0;
        bool                    self        = false;
    };

    struct Builder {
        InsVector           m_rpn;
        Stack<InsInfo>      m_stack;
        SymType             m_last  = SymType::None;
        
        Builder()
        {
            m_stack << InsInfo{};
        }

        std::error_code operator<<(const Symbol&sym)
        {
            return add(sym);
        }
        
        std::error_code    add(const Symbol&sym)
        {
            static const Repo& _r   = repo();
            switch(sym.type){
            case SymType::None:
                return {};
            case SymType::Error:
                return errors::existing_error();
            case SymType::Float:
                return add_float(sym);
            case SymType::Hex:
                return add_hex(sym);
            case SymType::Octal:
                return add_octal(sym);
            case SymType::Int:
                return add_integer(sym);
            case SymType::Text:
                return add_text(sym);
            case SymType::Operator:
                return add_operator(sym);
            default:
                return errors::todo();
            }
            return {};
        }

        std::error_code     add_binary(const Symbol& sym, const OpData& op)
        {
            return errors::todo();
        }
        
        std::error_code     add_close(const Symbol& sym, const OpData& op)
        {
            return errors::todo();
        }
        
        std::error_code     add_comma(const Symbol& sym, const OpData&)
        {
            ++(m_stack.back().commas);
            return {};
        }
        
        std::error_code     add_constant(const Symbol& sym)
        {
            m_rpn.push_back(Instruction{
                .code   = InsCode::Constant,
                .key    = sym.text
            });
            ++(m_stack.back().values);
            return {};
        }
        
        std::error_code    add_float(const Symbol& sym)
        {
            m_rpn.push_back(Instruction{
                .code   = InsCode::Value,
                .data   = Any((double) *to_double(sym.text))
            });
            ++(m_stack.back().values);
            return {};
        }
        
        std::error_code     add_function(const Symbol& sym)
        {
            m_stack << InsInfo{
                .type   = InsType::Function,
                .text   = sym.text
            };
            return {};
        }
        
        std::error_code     add_hex(const Symbol& sym)
        {
            m_rpn.push_back(Instruction{
                .code   = InsCode::Value,
                .data   = Any((uint64_t) *to_hex64(sym.text.substr(2)))
            });
            ++(m_stack.back().values);
            return {};
        }

        std::error_code     add_integer(const Symbol& sym)
        {
            m_rpn.push_back(Instruction{
                .code   = InsCode::Value,
                .data   = Any((int64_t) *to_int64(sym.text))
            });
            ++(m_stack.back().values);
            return {};
        }
        
        std::error_code     add_left(const Symbol& sym, const OpData& op)
        {
            return errors::todo();
        }
        
        std::error_code     add_octal(const Symbol& sym)
        {
            m_rpn.push_back(Instruction{
                .code   = InsCode::Value,
                .data   = Any((uint64_t) *to_octal64(sym.text))
            });
            ++(m_stack.back().values);
            return {};
        }
        
        std::error_code     add_operator(const Symbol& sym)
        {
			#if 0
            static const Repo& _r   = repo();
            
            const OpData*     setter      = nullptr;
            const OpData*     left        = nullptr;
            const OpData*     right       = nullptr;
            const OpData*     binary      = nullptr;
            const OpData*     trinary1    = nullptr;
            const OpData*     trinary2    = nullptr;
            const OpData*     open        = nullptr;
            const OpData*     close       = nullptr;
            const OpData*     comma       = nullptr;
            
            _r.all_operators(sym.text, [&](const OpData& data) {
                yInfo() << "Examining operator info (" << data.type << ") of " << data.text;
            
            
                switch(data.type){
                case OperatorType::None:
                    break;
                case OperatorType::Set:
                    setter       = &data;
                    break;
                case OperatorType::Left:
                    left        = &data;
                    break;
                case OperatorType::Right:
                    right       = &data;
                    break;
                case OperatorType::Binary:
                    binary      = &data;
                    break;
                case OperatorType::Trinary1:
                    trinary1    = &data;
                    break;
                case OperatorType::Trinary2:
                    trinary2    = &data;
                    break;
                case OperatorType::Open:
                    open        = &data;
                    break;
                case OperatorType::Close:
                    close       = &data;
                    break;
                case OperatorType::Comma:
                    comma       = &data;
                    break;
                }
            });
            
            if(setter && false)
                return add_setter(sym, *setter);
            if(comma)
                return add_comma(sym, *comma);
            if(open)
                return add_open(sym, *open);
            if(close)
                return add_close(sym, *close);
            if(trinary1)
                return add_trinary1(sym, *trinary1);
            if(trinary2)
                return add_trinary2(sym, *trinary2);
            if(left && false)
                return add_left(sym, *left);
            if(right && false)
                return add_right(sym, *right);
            if(binary && false)
                return add_binary(sym, *binary);
            #endif
            return errors::todo();
        }
        
        std::error_code     add_open(const Symbol& sym, const OpData& op)
        {
            m_stack << InsInfo{
                .type   = InsType::Open,
                .text   = sym.text,
                .other  = op.other
            };
            return {};
        }
        
        std::error_code     add_right(const Symbol& sym, const OpData& op)
        {
            return errors::todo();
        }
        
        std::error_code     add_setter(const Symbol& sym, const OpData& op)
        {
            return errors::todo();
        }

        std::error_code     add_text(const Symbol& sym)
        {
            static const Repo& _r   = repo();
            if(_r.has_constant(sym.text))
                return add_constant(sym);
            if(_r.has_function(sym.text))
                return add_function(sym);
            return add_variable(sym);
        }
        
        std::error_code     add_trinary1(const Symbol& sym, const OpData& op)
        {
            return errors::todo();
        }
        
        std::error_code     add_trinary2(const Symbol& sym, const OpData& op)
        {
            return errors::todo();
        }
        
        std::error_code     add_variable(const Symbol& sym)
        {
            m_rpn.push_back(Instruction{
                .code   = InsCode::Variable,
                .key    = sym.text
            });
            ++(m_stack.back().values);
            return {};
        }
    };

    Expect<InsVector>   compile(const SymVector& syms)
    {
        
        Builder build;
        if(syms.empty())
            return build.m_rpn;
        build.m_rpn.reserve(syms.size());
        
        std::error_code ec;
        for(const Symbol& sym : syms){
            ec  = build << sym;
            if(ec != std::error_code())
                return unexpected(ec);
            build.m_last    = sym.type;
        }
        
        if(build.m_stack.size() != 1)
            return errors::parenthesis_mismatch();
        return build.m_rpn;
    }
    
    Expect<InsVector>   compile(std::string_view in)
    {
        std::u32string  u32 = to_u32string(in);
        return compile(u32);
    }
    
    Expect<InsVector>   compile(std::u32string_view in)
    {
        Expect<SymVector>   syms    = tokenize(in);
        if(!syms)
            return unexpected(syms.error());
        return compile(*syms);
    }

    Expect<Any>         evaluate(const InsVector&insVec)
    {
        VarMap  vMap;
        return evaluate(insVec, vMap);
    }

    Expect<Any>         evaluate(const InsVector&insVec, VarMap&vmap)
    {
        const Repo& _r  = repo();
    
        Stack<Any>     theStack;
        for(const Instruction& ins : insVec){
            switch(ins.code){
            case InsCode::Assign:
                {
                    if(theStack.empty())
                        return errors::empty_stack();
                    vmap[ins.key] = std::move(theStack.pop());
                }
                break;
            case InsCode::Constant:
                {
                    auto x  = _r.constant(ins.key);
                    if(!x)
                        return errors::bad_constant();
                    theStack << *x;
                }
                break;
            case InsCode::Duplicate:
                if(theStack.empty())
                    return errors::empty_stack();
                theStack << theStack.top();
                break;
            case InsCode::Value:
                theStack << ins.data;
                break;
            case InsCode::Variable:
                {
                    auto i = vmap.find(ins.key);
                    if(i == vmap.end())
                        return errors::bad_variable();
                    theStack << i->second;
                }
                break;
            default:
                return errors::bad_instruction();
            }
        }
        
        if(theStack.empty())
            return errors::empty_stack();
        if(theStack.size() > 1)
            return errors::mulitple_values();
        return theStack.pop();
    }
    
}

