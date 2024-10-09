////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/basic/Ref.hpp>
#include <yq-toolbox/container/Stack.hpp>
#include <yq/userexpr/forward.hpp>

namespace yq::expr {

    class Compiler {
    public:

        Compiler(const Context& ctx, Analysis& rAnalysis, Ref<VirtualMachine> vm);
        std::error_code     compile(const SymVector& syms);
        std::error_code     add(const Symbol& sym);
    
    private:
        const Context&                  m_context;
        Ref<VirtualMachine>             m_machine;
        Analysis&                       m_analysis;
        SymDataStack                    m_pending;
        //Stack<const TypeInfo*>          m_types;
        int                             m_stack     = 0;
        
        
        SymData*    opening();
        
        void        decl_value();
        
        std::error_code     add_assignment(const Symbol& sym);
        
        std::error_code     add_close(const Symbol& sym);

        std::error_code     add_comma(const Symbol& sym);
        
        std::error_code     add_constant(const Symbol& sym);

        std::error_code     add_constructor(const Symbol& sym);

        std::error_code     add_duplicate(const Symbol& sym);
        std::error_code     add_float(const Symbol& sym);

        std::error_code     add_function(const Symbol& sym);

        std::error_code     add_hexadecimal(const Symbol& sym);

        std::error_code     add_integer(const Symbol& sym);

        std::error_code     add_octal(const Symbol& sym);

        std::error_code     add_open(const Symbol& sym);

        std::error_code     add_operator(const Symbol& sym);
        std::error_code     add_special(const Symbol& sym);
        std::error_code     add_text(const Symbol& sym);
        std::error_code     add_value(const Symbol& sym);
        std::error_code     add_variable(const Symbol& sym);
        
        std::error_code     pop();

        std::error_code     pop_assignment(const SymData&sym);

        std::error_code     pop_constructor(const SymData&);

        std::error_code     pop_duplicate(const SymData&sym);

        std::error_code     pop_function(const SymData& sd);


        std::error_code     pop_operator(const SymData& sym);

        
        std::error_code     push(InstructionCPtr insptr);
        
    };
    
}

