////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/math/expr/preamble.hpp>
#include <0/basic/Ref.hpp>
#include <variant>

namespace yq::expr {
    
    /*! User expression instruction
    
        We'd tried a common class to symbols, but that's an ugly hack.
    */
    class Instruction : public RefCount {
    public:
    
        using result_t  = std::variant<std::monostate, int, const TypeInfo*, std::vector<const TypeInfo*>>;

        // Defining text
        string_view_t               text() const { return m_text; }
        
        //! Executes this instruction
        virtual std::error_code     execute(any_stack_t&, Context&) const = 0;
        
        //! Expected result (monostate if unknown)
        virtual result_t    result() const;
        
        //! Expected result for argument types
        virtual result_t    result(std::span<const TypeInfo*>) const;
        
        virtual uint16_t     pop_count() const { return 0xFFFF; }
        virtual uint16_t     push_count() const { return 0xFFFF; }
        
        //! Destructor
        virtual ~Instruction();

    protected:
        Instruction(const string_t&);
        
        const string_t  m_text;
    };
}
