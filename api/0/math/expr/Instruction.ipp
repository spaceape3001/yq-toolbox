////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Instruction.hpp"
#include <0/basic/TextUtils32.hpp>

namespace yq::expr {
    Expect<InsVector>   compile(const SymVector& syms)
    {
        InsVector       ret;
        if(syms.empty())
            return ret;
            
        ret.reserve(syms.size());
        for(const Symbol& sym : syms){
            std::error_code ec;
            switch(sym.type){
            case SymType::None:
                continue;
            case SymType::Error:
                return errors::existing_error();
            case SymType::Float:
                ret.push_back(Instruction{
                    .code   = InsCode::Value,
                    .data   = Any((double) *to_double(sym.text))
                });
                break;
            case SymType::Hex:
                ret.push_back(Instruction{
                    .code   = InsCode::Value,
                    .data   = Any((uint64_t) *to_hex64(sym.text.substr(2)))
                });
                break;
            case SymType::Octal:
                ret.push_back(Instruction{
                    .code   = InsCode::Value,
                    .data   = Any((uint64_t) *to_octal64(sym.text))
                });
                break;
            case SymType::Int:
                ret.push_back(Instruction{
                    .code   = InsCode::Value,
                    .data   = Any((int64_t) *to_int64(sym.text))
                });
                break;
            case SymType::Text:
                if(has_constant(sym.text)){
                    ret.push_back(Instruction{
                        .code   = InsCode::Constant,
                        .key    = sym.text
                    });
                }
                break;
            default:
                return errors::todo();
            }
        }
        
        return ret;
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
    
        std::stack<Any>     theStack;
        for(const Instruction& ins : insVec){
            switch(ins.code){
            case InsCode::Assign:
                {
                    if(theStack.empty())
                        return errors::empty_stack();
                    vmap[ins.key] = std::move(theStack.top());
                    theStack.pop();
                }
                break;
            case InsCode::Constant:
                {
                    auto x  = constant(ins.key);
                    if(!x)
                        return errors::bad_constant();
                    theStack.push(*x);
                }
                break;
            case InsCode::Duplicate:
                if(theStack.empty())
                    return errors::empty_stack();
                theStack.push(theStack.top());
                break;
            case InsCode::Value:
                theStack.push(ins.data);
                break;
            case InsCode::Variable:
                {
                    auto i = vmap.find(ins.key);
                    if(i == vmap.end())
                        return errors::bad_variable();
                    theStack.push(i->second);
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
        
        Any ret = std::move(theStack.top());
        theStack.pop();
        return ret;
    }
    
}

