////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/math/expr/preamble.hpp>

#include <0/basic/Any.hpp>
#include <yq/basic/Ref.hpp>
#include <yq/text/MaybeCase.hpp>
#include <0/math/preamble.hpp>
#include <yq/math/Operator.hpp>

#include <iosfwd>
#include <set>
#include <string>
#include <string_view>
#include <system_error>
#include <unordered_set>
#include <vector>



namespace yq {

    /*! \brief User defined expressions
    
        Premise is... take text in, parse it, and evaluate it.  It'll be 
        less efficient than straight up code, but allows the flexibility.
        So, DON'T put this into critical high-update paths, if possible.
    
    */
    class UserExpr {
    public:
        using SymVector     = expr::SymVector;
    
    
        UserExpr();
        UserExpr(const UserExpr&);
        UserExpr(UserExpr&&);
        UserExpr& operator=(const UserExpr&);
        UserExpr& operator=(UserExpr&&);
        ~UserExpr();

        explicit UserExpr(std::string_view);
        explicit UserExpr(std::u32string_view);

        const std::u32string&   definition() const { return m_definition; }
        const SymVector&        algebra() const { return m_algebra; }
        
        constexpr bool          is_good() const { return m_machine.valid(); }
        std::error_code         build_error() const { return m_buildError; }
        
        Expect<Any>             evaluate() const;
        Expect<Any>             evaluate(expr::Context&) const;
        

    private:
        SymVector			        m_algebra;
        Ref<expr::VirtualMachine>   m_machine;
        
        std::u32string          m_definition;
        std::error_code         m_buildError     = {};
        
        
        std::error_code         _init(std::u32string_view);
    };
}

