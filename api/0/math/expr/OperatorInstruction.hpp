////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/basic/Any.hpp>
#include <0/math/expr/Instruction.hpp>

namespace yq::expr {
    const OperatorInfo*     find_operator(std::span<const Any>, Operator opCode);
    const OperatorInfo*     find_operator(std::span<const TypeInfo*>, Operator opCode);


    
    /*! \brief Dynamic operator when argument types aren't known until runtime
    */
    class OperatorDynamic : public Instruction {
    public:
    
        OperatorDynamic(const SymData&sym);
        std::error_code     execute(any_stack_t&values, Context&ctx) const override;
        uint16_t            pop_count() const override { return m_args; }
        uint16_t            push_count() const override { return 1; }
        
        const Operator      m_operator;
        const unsigned int  m_args;
    };
    
    class OperatorFixed : public Instruction {
    public:
        OperatorFixed(const SymData& sym, const OperatorInfo* opinfo);
        std::error_code     execute(any_stack_t&values, Context&ctx) const override;
        uint16_t            pop_count() const override { return m_args; }
        uint16_t            push_count() const override { return 1; }
        result_t            result() const override;
        
    private:
        result_t                m_result;
        const OperatorInfo*     m_opInfo;
        const unsigned int      m_args;
    };
    
}
