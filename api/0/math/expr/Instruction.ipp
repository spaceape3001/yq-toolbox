////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Instruction.hpp"
#include "Symbol.hpp"
//#include "Repo.hpp"
#include <0/basic/TextUtils32.hpp>
#include <0/basic/Stack.hpp>

namespace yq::expr {
    struct InsInfo {
        
    };

    struct Builder {
        InsVector           m_rpn;
        Stack<InsInfo>      m_stack;
        
        Builder()
        {
            m_stack << InsInfo{};
        }
        
        std::error_code     add_operator(const Symbol& sym)
        {
            static const Repo& _r   = repo();
            bool success = _r.all_operators(sym.text, [&](const Repo::OpData& data) -> bool {
                switch(data.type){
                case OperatorType::None:
                    break;
                case OperatorType::Set:
                    break;
                case OperatorType::Left:
                    break;
                case OperatorType::Right:
                    break;
                case OperatorType::Binary:
                    break;
                case OperatorType::Trinary1:
                    break;
                case OperatorType::Trinary2:
                    break;
                case OperatorType::Open:
                    break;
                case OperatorType::Close:
                    break;
                }
                return false;
            });
            
            if(!success)
                return errors::bad_operator();
            return errors::todo();
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
                m_rpn.push_back(Instruction{
                    .code   = InsCode::Value,
                    .data   = Any((double) *to_double(sym.text))
                });
                return {};
            case SymType::Hex:
                m_rpn.push_back(Instruction{
                    .code   = InsCode::Value,
                    .data   = Any((uint64_t) *to_hex64(sym.text.substr(2)))
                });
                return {};
            case SymType::Octal:
                m_rpn.push_back(Instruction{
                    .code   = InsCode::Value,
                    .data   = Any((uint64_t) *to_octal64(sym.text))
                });
                return {};
            case SymType::Int:
                m_rpn.push_back(Instruction{
                    .code   = InsCode::Value,
                    .data   = Any((int64_t) *to_int64(sym.text))
                });
                return {};
            case SymType::Text:
                if(_r.has_constant(sym.text)){
                    m_rpn.push_back(Instruction{
                        .code   = InsCode::Constant,
                        .key    = sym.text
                    });
                    return {};
                } 
                
                if(_r.has_function(sym.text)){
                #if 0
                    temp << Instruction{
                        .code   = InsCode::Function,
                        .key    = sym.text
                    };
                    break;
                #endif
                    return errors::todo();
                }
                
                m_rpn.push_back(Instruction{
                    .code   = InsCode::Variable,
                    .key    = sym.text
                });
                
                break;
            case SymType::Operator:
                return add_operator(sym);
            default:
                return errors::todo();
            }
            return {};
        }
        
        std::error_code operator<<(const Symbol&sym)
        {
            return add(sym);
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
        }
        
        if(build.m_stack.size() != 1)
            return errors::parenthesis_mismatch();
        return build.m_rpn;
        
        #if 0
        
        InsVector           ret;
        if(syms.empty())
            return ret;

        Stack<Instruction>    temp;
        temp << Instruction{};      // padding for top element
            
        ret.reserve(syms.size());
        for(const Symbol& sym : syms){
            std::error_code ec;
            switch(sym.type){
            case SymType::Operator:
                {
                }
                break;
            default:
                return errors::todo();
            }
        }
        
        if(temp.size() != 1)
            return errors::parenthesis_mismatch();
        
        return ret;
        #endif
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

