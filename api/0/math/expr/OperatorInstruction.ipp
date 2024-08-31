////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "OperatorInstruction.hpp"

#include <yq/errors.hpp>
#include <yq/basic/Stack.hpp>
#include <0/math/expr/SymData.hpp>

namespace yq::expr {
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

    const OperatorInfo*     find_operator(std::span<const TypeInfo*> span, Operator opCode)
    {
        if(span.size() == 0)
            return nullptr;
        for(const TypeInfo* ti : span){
            if(!ti)
                return nullptr;
        }
            
        const OperatorInfo* best    = nullptr;
        int                 score   = 0;
        
        const TypeInfo& ti  = *(span[0]);
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

    OperatorDynamic::OperatorDynamic(const SymData&sym) : 
        Instruction(sym.text), m_operator((Operator) sym.kind), m_args(sym.argcnt)
    {
    }
    
    std::error_code     OperatorDynamic::execute(any_stack_t&values, Context&ctx) const
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

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    OperatorFixed::OperatorFixed(const SymData& sym, const OperatorInfo* opinfo) : Instruction(sym.text), 
        m_opInfo(opinfo), m_args(sym.argcnt)
    {
        const TypeInfo* ar  = opinfo->result_type();
        if(ar){
            m_result        = ar;
        }
    }
    
    std::error_code     OperatorFixed::execute(any_stack_t&values, Context&ctx) const
    {
        if(values.size() < m_args){
            return errors::insufficient_arguments();
        }
        
        Expect<Any>   res = m_opInfo->invoke(values.top_cspan(m_args));
        if(!res)
            return res.error();
        values.pop_last(m_args);
        values << std::move(*res);
        return {};
    }

    Instruction::result_t   OperatorFixed::result() const 
    { 
        return m_result;
    }


}
