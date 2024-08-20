////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/basic/preamble.hpp>
#include <0/basic/Any.hpp>
#include <0/basic/Ref.hpp>
#include <0/basic/MaybeCase.hpp>
#include <0/math/preamble.hpp>
#include <0/math/Operator.hpp>
//#include <0/math/expr/preamble.hpp>
//#include <0/math/expr/Symbol.hpp>
//#include <0/math/expr/Instruction.hpp>

#include <functional>
#include <iosfwd>
#include <set>
#include <string>
#include <string_view>
#include <system_error>
#include <unordered_set>
#include <vector>

namespace log4cpp { class CategoryStream; }


//namespace yq::expr {
    //bool                has_function(const std::u32string&);
    //bool                has_constant(std::string_view);
    //bool                has_constant(const std::u32string&);
    //Expect<Any>         constant(std::string_view);
    //Expect<Any>         constant(const std::u32string&);
//}

namespace yq::expr {
    class Instruction;
    struct Symbol;
    struct SymCode;
    struct SymData;
    struct Token;
    using SymVector     = std::vector<Symbol>;
    using TokenFN       = std::function<std::error_code(SymCode,std::u32string_view)>;
    using InstructionCPtr       = Ref<const Instruction>;
    
    using u32string_type_map_t  = std::map<std::u32string,const TypeInfo*,IgCase>;
    
    struct Context;
    struct Analysis;
    using SymDataStack  = Stack<SymData>;
}


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
        
        constexpr bool          is_good() const { return m_instruction.valid(); }
        std::error_code         build_error() const { return m_buildError; }
        
        Expect<Any>             evaluate() const;
        Expect<Any>             evaluate(expr::Context&) const;
        

    private:
        SymVector			    m_algebra;
        expr::InstructionCPtr   m_instruction;
        
        std::u32string          m_definition;
        std::error_code         m_buildError     = {};
        
        
        std::error_code         _init(std::u32string_view);
    };
}

