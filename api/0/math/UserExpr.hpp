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


namespace yq {
    class UserExpr {
    public:

		struct OpData;
		struct Repo;
		struct Symbol;
		struct SymCode;
		struct SymData;
		struct Token;

		using SymVector = std::vector<Symbol>;
        using TokenFN   = std::function<std::error_code(SymCode,std::u32string_view)>;

        using SymStack  = Stack<Symbol>;

		static Repo& repo();
        
        /*! \brief Sub-tokenizes
        
            This is the sub-tokenizer, it scans the text for what seems like the next
            relevant symbol.  
        */
        static Token        token(std::u32string_view);
        
        
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
        
        static std::error_code s1_open_close(SymVector&);
        static std::error_code s2_signs(SymVector&);
        static std::error_code s3_operators(SymVector&);
        static std::error_code s4_interpret_values(SymVector&);
    };

    log4cpp::CategoryStream&    operator<<(log4cpp::CategoryStream&, const UserExpr::Symbol&);
    log4cpp::CategoryStream&    operator<<(log4cpp::CategoryStream&, const UserExpr::SymVector&);
    log4cpp::CategoryStream&    operator<<(log4cpp::CategoryStream&, const UserExpr::Token&);
    std::ostream&    operator<<(std::ostream&, const UserExpr::Symbol&);
    std::ostream&    operator<<(std::ostream&, const UserExpr::SymVector&);
    std::ostream&    operator<<(std::ostream&, const UserExpr::Token&);
}

