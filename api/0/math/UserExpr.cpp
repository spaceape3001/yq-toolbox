////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "UserExpr.hpp"

#include <0/basic/errors.hpp>
#include <0/basic/Logging.hpp>
#include <0/basic/TextUtils.hpp>
#include <tbb/spin_rw_mutex.h>
#include <stack>

namespace yq::expr {

    static constexpr bool       kDigitsText         = true;
    static constexpr bool       kPunctStartsText    = true;

    struct Repo {
        mutable tbb::spin_rw_mutex  mutex;
        ConMap                      constants;
        OpMap                       operators;
        FnMap                       functions;
        C32Hash                     punctText;
        
        Repo()
        {
            constants[U"pi"]     = std::numbers::pi_v<double>;
            constants[U"sqrt2"]  = std::numbers::sqrt2_v<double>;
            constants[U"sqrt3"]  = std::numbers::sqrt3_v<double>;
            constants[U"e"]      = std::numbers::e_v<double>;
            constants[U"ln2"]    = std::numbers::ln2_v<double>;
            constants[U"ln10"]   = std::numbers::ln10_v<double>;
            constants[U"egamma"] = std::numbers::egamma_v<double>;
            punctText.insert(U'_');
        }
    };
    
    Repo&   repo()
    {
        static Repo s_repo;
        return s_repo;
    }
    
    #define LOCK                                                        \
        static const Repo&  _r  = repo();                               \
        tbb::spin_rw_mutex::scoped_lock     _lock(_r.mutex, false);
    
    #define WLOCK                                                        \
        static Repo&  _r  = repo();                                     \
        tbb::spin_rw_mutex::scoped_lock     _lock(_r.mutex, true);

}

#include "expr/Instruction.ipp"
#include "expr/Symbol.ipp"

namespace yq::expr {
    Expect<Any>         constant(std::string_view sv)
    {
        std::u32string      u32 = to_u32string(sv);
        return constant(u32);
    }
    
    Expect<Any>         constant(const std::u32string& k)
    {
        {
            LOCK
            auto i  = _r.constants.find(k);
            if(i != _r.constants.end())
                return i->second;
        }
        return errors::bad_argument();
    }

    bool                has_constant(std::string_view k)
    {
        std::u32string u32  = to_u32string(k);
        return has_constant(u32);
    }
    
    bool                has_constant(const std::u32string& k)
    {
        LOCK
        return _r.constants.contains(k);
    }

    void                set_constant(const std::u32string& k, const Any& v)
    {
        WLOCK
        _r.constants[k] = v;
    }
    
    void                set_constant(std::string_view k, const Any&v)
    {
        std::u32string u32  = to_u32string(k);
        set_constant(u32, v);
    }

    void                set_constant(const std::u32string&k, Any&&v)
    {
        WLOCK
        _r.constants[k] = std::move(v);
    }
    
    void                set_constant(std::string_view k, Any&&v)
    {
        std::u32string u32  = to_u32string(k);
        set_constant(u32, std::move(v));
    }



    #undef LOCK
    #undef WLOCK
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace yq {
    UserExpr::UserExpr() = default;
    UserExpr::UserExpr(const UserExpr&) = default;
    UserExpr::UserExpr(UserExpr&&) = default;
    UserExpr& UserExpr::operator=(const UserExpr&) = default;
    UserExpr& UserExpr::operator=(UserExpr&&) = default;
    UserExpr::~UserExpr() = default;
}


#if 0

#include "expr/Symbol.ipp"
#include <0/basic/Any.hpp>
#include <0/basic/errors.hpp>
#include <tbb/spin_rw_mutex.h>

namespace yq {
    struct UserExpr::Repo {
        AnyIgCaseMap                    constants;
        Grammar                         grammar;
        mutable tbb::spin_rw_mutex      mutex;
        
        Repo()
        {
            constants["pi"]     = std::numbers::pi_v<double>;
            constants["e"]      = std::numbers::e_v<double>;
            constants["sqrt2"]  = std::numbers::sqrt2_v<double>;
            constants["sqrt3"]  = std::numbers::sqrt3_v<double>;
            constants["ln2"]    = std::numbers::ln2_v<double>;
            constants["ln10"]   = std::numbers::ln10_v<double>;
            constants["egamma"] = std::numbers::egamma_v<double>;
        }
    };
    
    UserExpr::Repo& UserExpr::repo()
    {
        static Repo s_repo;
        return s_repo;
    }

    #define LOCK                                                \
        const Repo&   _r  = repo();                             \
        tbb::spin_rw_mutex::scoped_lock _lock(_r.mutex, false);
    
    #define WLOCK                                               \
        Repo&   _r  = repo();                                   \
        tbb::spin_rw_mutex::scoped_lock _lock(_r.mutex, true);
    

    
    Expect<Any>      UserExpr::constant(const std::string& k)
    {
        if(k.empty())
            return errors::empty_key();

        {
            LOCK
            auto x = _r.constants.find(k);
            if(x != _r.constants.end())
                return x->second;
        }

        return errors::key_not_found();
    }

    const UserExpr::Grammar&       UserExpr::default_grammar()
    {
        return repo().grammar;
    }

    std::error_code  UserExpr::set_constant(const std::string&k, Any&& val)
    {
        if(k.empty())
            return errors::empty_key();
        {
            WLOCK
            _r.constants[k] = std::move(val);
        }
        return std::error_code();
    }
    
    ////////////////////////////////////////////////////////////////////////////////

    Expect<Any>          UserExpr::execute(std::string_view text, const Grammar&g, Context* ctx)
    {
        auto cnd    = parse(text, g);
        if(!cnd)
            return unexpected(cnd.error());
        UserExpr    uex = std::move(*cnd);
        return uex.evaluate(ctx);
    }

    Expect<UserExpr>     UserExpr::parse(std::string_view, const Grammar&g)
    {
        UserExpr    ret;
        
        return errors::todo();
    }
    
    ////////////////////////////////////////////////////////////////////////////////
    
    UserExpr::UserExpr() = default;
    UserExpr::UserExpr(const UserExpr&) = default;
    UserExpr::UserExpr(UserExpr&&) = default;
    UserExpr& UserExpr::operator=(const UserExpr&) = default;
    UserExpr& UserExpr::operator=(UserExpr&&) = default;
    UserExpr::~UserExpr() = default;
    
    ////////////////////////////////////////////////////////////////////////////////

    Expect<Any>         UserExpr::evaluate(Context* ctx) const
    {
        return errors::todo();
    }

    ////////////////////////////////////////////////////////////////////////////////

    UserExpr::Context::Context() = default;
    UserExpr::Context::Context(const Context&) = default;
    UserExpr::Context::Context(Context&&) = default;
    UserExpr::Context& UserExpr::Context::operator=(const Context&) = default;
    UserExpr::Context& UserExpr::Context::operator=(Context&&) = default;
    UserExpr::Context::~Context() = default;

    UserExpr::Context::Context(const Options& opts) : m_variables(MaybeCase(opts.varIgCase)), m_options(opts)
    {
    }

    Expect<Any> UserExpr::Context::variable(const std::string&k) const
    {
        if(k.empty())
            return errors::empty_key();
        return errors::todo();
    }
    
    std::error_code UserExpr::Context::set_variable(const std::string&k, Any&&val)
    {
        if(k.empty())
            return errors::empty_key();
        m_variables[k]   = std::move(val);
        return std::error_code();
    }

    ////////////////////////////////////////////////////////////////////////////////

    UserExpr::Grammar::Grammar() = default;
    UserExpr::Grammar::Grammar(const Grammar&) = default;
    UserExpr::Grammar::Grammar(Grammar&&) = default;
    UserExpr::Grammar& UserExpr::Grammar::operator=(const Grammar&) = default;
    UserExpr::Grammar& UserExpr::Grammar::operator=(Grammar&&) = default;
    UserExpr::Grammar::~Grammar() = default;

    ////////////////////////////////////////////////////////////////////////////////


}
#endif

