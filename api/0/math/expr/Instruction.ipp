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
    Expect<InsVector>   compile(const SymVector& syms)
    {
        static const Repo& _r   = repo();
        InsVector           ret;
        if(syms.empty())
            return ret;
        Stack<Instruction>    temp;
            
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
                if(_r.has_constant(sym.text)){
                    ret.push_back(Instruction{
                        .code   = InsCode::Constant,
                        .key    = sym.text
                    });
                }
                if(_r.has_function(sym.text)){
                    temp << Instruction{
                        .code   = InsCode::Function,
                        .key    = sym.text
                    };
                }
                break;
            case SymType::Operator:
                {
                    bool success = _r.all_operators(sym.text, [&](const Repo::OpData&) -> bool {
                        return false;
                    });
                    return errors::todo();
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

