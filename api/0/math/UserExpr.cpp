////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <0/math/expr/Repo.ipp>

namespace yq::expr {
    Repo&   repo() 
    {   
        return Repo::instance();
    }
}

#include "expr/Instruction.ipp"
#include "expr/Symbol.ipp"
#include "UserExpr.hpp"


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace yq {
    UserExpr::UserExpr() = default;
    UserExpr::UserExpr(const UserExpr&) = default;
    UserExpr::UserExpr(UserExpr&&) = default;
    UserExpr& UserExpr::operator=(const UserExpr&) = default;
    UserExpr& UserExpr::operator=(UserExpr&&) = default;
    UserExpr::~UserExpr() = default;

    UserExpr::UserExpr(std::string_view sv)
    {
		std::u32string 	u32	= to_u32string(sv);
		_init(u32);
	}
	
    UserExpr::UserExpr(std::u32string_view uin)
    {
		_init(uin);
	}

	void    UserExpr::_init(std::u32string_view) 
	{
	}

    Expect<Any>     UserExpr::evaluate() const
    {
        expr::VarMap    variables;
        return evaluate(variables);
    }

    Expect<Any>     UserExpr::evaluate(expr::VarMap& variables) const
    {
        if(!m_good)
            return errors::bad_userexpr();
        return expr::evaluate(m_instructions, variables);
    }
}


#if 0
#include <0/basic/Logging.hpp>
#include <0/basic/MultiMap.hpp>
#include <0/basic/TextUtils.hpp>
#include <tbb/spin_rw_mutex.h>
#include <stack>

namespace yq::expr {

    static constexpr bool       kDigitsText         = true;
    static constexpr bool       kPunctStartsText    = true;

    //! General category of operation
    enum class Flop {
        None    = 0,
        //! Setter (so won't have any operator)
        Set,
        //! Unary with operator on left side
        Left,
        //! Unary with operator on right side
        Right,
        //! Standard binary (a+b)
        Binary,
        //! Open-mark
        Open,
        //! Close-mark
        Close
    };
    
}
#endif
