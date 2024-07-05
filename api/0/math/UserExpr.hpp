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
#include <0/math/expr/preamble.hpp>
#include <0/math/expr/Symbol.hpp>
#include <0/math/expr/Instruction.hpp>

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
        UserExpr();
        UserExpr(const UserExpr&);
        UserExpr(UserExpr&&);
        UserExpr& operator=(const UserExpr&);
        UserExpr& operator=(UserExpr&&);
        ~UserExpr();

        explicit UserExpr(std::string_view);
        explicit UserExpr(std::u32string_view);

        const std::u32string&   definition() const { return m_definition; }
        const expr::SymVector&  symbols() const { return m_symbols; }
        const expr::InsVector&  instructions() const { return m_instructions; }
        bool                    is_good() const { return m_good; }
        
        Expect<Any>     evaluate() const;
        Expect<Any>     evaluate(expr::VarMap&) const;
        

    private:
        expr::SymVector     m_symbols;
        expr::InsVector     m_instructions;
        std::u32string      m_definition;
        bool                m_good          = false;
        
        void    _init(std::string_view);
        void    _init(std::u32string_view);
    };
}

#if 0

namespace yq {

    /*! \brief User Expression
    
        A user expression is about evaluating a user provided string, 
        and operating on it.  This won't be as efficient as say compiled
        or inpreted code, it'll work in a pinch.
    */
    class UserExpr {
    public:
    
        //! Sets a system-wide constant (think PI)
        static Expect<Any>      constant(const std::string& key);
        static std::error_code  set_constant(const std::string& key, Any&& value);
    
        struct Instruction;
        struct Symbol;
        class Context;
        class Grammar;
        
        Expect<Any>         evaluate(Context* ctx=nullptr) const;
        
        const std::vector<Symbol>&      symbols() const { return m_symbols; }
        const std::vector<Instruction>& execution() const { return m_execution; }
        
        UserExpr();
        UserExpr(const UserExpr&);
        UserExpr(UserExpr&&);
        UserExpr& operator=(const UserExpr&);
        UserExpr& operator=(UserExpr&&);
        ~UserExpr();

        const std::string&  definition() const { return m_definition; }

        static const Grammar&       default_grammar();
        static Expect<UserExpr>     parse(std::string_view, const Grammar&g=default_grammar());
        
        //! Shortcut for parse/evaluate
        static Expect<Any>          execute(std::string_view, const Grammar&g=default_grammar(), Context* ctx=nullptr);
        
        enum class Code {
            NOP     = 0,
            Value,
            Operator,
            Variable,
            Function,
            Open,
            Close
        };

    private:

        using AnyIgCaseMap  = std::map<std::string,Any,IgCase>;
        using VarMap        = std::map<std::string,Any,MaybeCase>;
    
        std::vector<Symbol>         m_symbols;
        std::vector<Instruction>    m_execution;
        std::string                 m_definition;
    
        struct Repo;
        static Repo& repo();
    };
    
    /*! \brief Context
    
        Context is a collection of variables/functions/etc 
    */
    class UserExpr::Context {
    public:
        struct Options {
            bool    varIgCase   = false;
        };

        Context();
        Context(const Options& opts);
        Context(const Context&);
        Context(Context&&);
        Context& operator=(const Context&);
        Context& operator=(Context&&);
        ~Context();

        Expect<Any> variable(const std::string&) const;
        std::error_code set_variable(const std::string&, Any&&);
        
    private:
        
        VarMap      m_variables;
        Options     m_options;
    };
    
    class UserExpr::Grammar {
    public:
    
        Grammar();
        Grammar(const Grammar&);
        Grammar(Grammar&&);
        Grammar& operator=(const Grammar&);
        Grammar& operator=(Grammar&&);
        ~Grammar();
    
    };
    
    struct UserExpr::Symbol {
        std::string_view  text;
    };
    
    struct UserExpr::Instruction {
        
        
        Code            code;
    };
}

#endif
