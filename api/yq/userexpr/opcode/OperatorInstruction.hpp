////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Any.hpp>
#include <yq/userexpr/forward.hpp>
#include <yq/userexpr/impl/Instruction.hpp>

namespace yq::expr {
    const OperatorMeta*     find_operator(std::span<const Any>, Operator opCode);
    const OperatorMeta*     find_operator(std::span<const TypeMeta*>, Operator opCode);


    
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
        OperatorFixed(const SymData& sym, const OperatorMeta* opinfo);
        std::error_code     execute(any_stack_t&values, Context&ctx) const override;
        uint16_t            pop_count() const override { return m_args; }
        uint16_t            push_count() const override { return 1; }
        result_t            result() const override;
        
    private:
        result_t                m_result;
        const OperatorMeta*     m_opInfo;
        const unsigned int      m_args;
    };
    
}
