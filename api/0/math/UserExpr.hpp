////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/basic/preamble.hpp>
#include <0/basic/Any.hpp>
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
    struct Token;
    using SymVector     = std::vector<Symbol>;
    using TokenFN       = std::function<std::error_code(SymCode,std::u32string_view)>;
}


namespace yq {

    /*! \brief User defined expressions
    
        Premise is... take text in, parse it, and evaluate it.  It'll be 
        less efficient than straight up code, but allows the flexibility.
        So, DON'T put this into critical high-update paths, if possible.
    
    */
    class UserExpr {
    public:

        using Symbol        = expr::Symbol;
        using Instruction   = expr::Instruction;
        using Token         = expr::Token;
        using SymCode       = expr::SymCode;
        using SymVector     = expr::SymVector;
        using TokenFN       = expr::TokenFN;

		struct SymData;


        using SymStack      = Stack<Symbol>;
        using SymDataStack  = Stack<SymData>;
        
        
        static Expect<SymVector>   tokenize(std::string_view);
        static Expect<SymVector>   tokenize(std::u32string_view);
        
        static std::error_code  tokenize(std::u32string_view, SymVector&);
        static std::error_code  tokenize(std::string_view, SymVector&);

        static std::error_code  tokenize(std::u32string_view, TokenFN&&);
        static std::error_code  tokenize(std::string_view, TokenFN&&);
        
        static std::error_code  streamline(SymVector&);
		
		//	We'll fold things together once this all works
		static std::error_code	algebra_to_rpn(SymVector&, const SymVector&);
        static Expect<Any>      execute(u32string_any_map_t&, const SymVector&);
    
    
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
        const SymVector&        rpn() const { return m_rpn; }
        constexpr bool          is_good() const { return m_buildError == std::error_code(); }
        std::error_code         build_error() const { return m_buildError; }
        
        Expect<Any>     evaluate() const;
        Expect<Any>     evaluate(u32string_any_map_t&) const;
        

    private:
        SymVector			m_algebra;
        SymVector			m_rpn;
        
        std::u32string      m_definition;
        std::error_code     m_buildError     = {};
        
        
        std::error_code    _init(std::u32string_view);
        
        static std::error_code          s_open_close(SymVector&);
        static std::error_code          s_signs(SymVector&);
        static std::error_code          s_operators(SymVector&);
        static std::error_code          s_values(SymVector&);
        static std::error_code          s_functions(SymVector&);
        static std::error_code          s_constants(SymVector&);
        
        static SymData*                 a2r_top_open(SymDataStack&);
        //! Declares that we have a value for current open
        static void                     a2r_decl_value(SymDataStack&);
        
        static const OperatorInfo*      x_operator_find(std::span<const Any>, Operator);
        static const MethodInfo*        x_function_find(any_stack_t&, const Symbol&);
        static const ConstructorInfo*   x_constructor_find(any_stack_t&, const Symbol&);

        static std::error_code          x_operator(any_stack_t&, const Symbol&);
        static std::error_code          x_assign(any_stack_t&, u32string_any_map_t&, const Symbol&);
        static std::error_code          x_constant(any_stack_t&, const Symbol&);
        static std::error_code          x_constructor(any_stack_t&, const Symbol&);
        static std::error_code          x_function(any_stack_t&, const Symbol&);
        static std::error_code          x_function_zero(any_stack_t&, const Symbol&);
        static std::error_code          x_function_one(any_stack_t&, const Symbol&);
        static std::error_code          x_function_more(any_stack_t&, const Symbol&);
        static std::error_code          x_special(any_stack_t&, u32string_any_map_t&, const Symbol&);
        static std::error_code          x_text(any_stack_t&, const u32string_any_map_t&, const Symbol&);
        static std::error_code          x_value(any_stack_t&, const Symbol&);
        static std::error_code          x_variable(any_stack_t&, const u32string_any_map_t&, const Symbol&);
    };

}

