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
		m_good = _init(u32);
	}
	
    UserExpr::UserExpr(std::u32string_view uin)
    {
		m_good = _init(uin);
	}

	bool    UserExpr::_init(std::u32string_view uxpr) 
	{
		// todo
		auto deck	= expr::tokenize(uxpr);
		if(!deck){
			yInfo() << deck.error();
			return false;
		}
		
		m_symbols	= std::move(deck.value());
		auto ec	= expr::streamline(m_symbols);
		if(!ec){
			yInfo() << ec;
			return false;
		}
		
		return false;
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

namespace yq::expr {

    struct SymData : public Symbol {
		SymData(const Symbol& sym) : Symbol(sym) {}
	};
	
#if 0
	void            zuserexpr::makeRpn()
	{
		m_rpn.clear();
		m_rpn.reserve(m_algebra.size());
		zstack<Operation*>     stk;
		Operation*               u;
		
		for(Symbol* s : m_algebra){
			if(!s)
				continue;
				
			switch( s-> type){
			case ST_None:
				break;
			case ST_Operator:
				u   = static_cast<Operation*>(s);
				if(!u)          // bad....
					break;
				
				for(;;){
					if(stk.empty())
						break;
					   
					Operation* p   = stk.top(nullptr);
					if(p->type == ST_Open)
						break;
					if((p->type == ST_Operator) && (p->priority < u->priority))
						break;
					m_rpn << stk.pop();
				}
				stk << u;
				break;
			case ST_Function:
				stk << static_cast<Operation*>(s);
				break;
			case ST_Value:
			case ST_Variable:
				m_rpn << s;
				break;
			case ST_Open:
				stk << static_cast<Operation*>(s);
				break;
			case ST_Close:
				while(!stk.empty() && stk.top()->type != ST_Open){
					m_rpn << stk.pop();
				}
				break;
			}
		}
		
		while(!stk.empty()){
			m_rpn << stk.pop();
		}
	}
#endif

    Expect<SymVector>	compile_rpn(const SymVector& input)
    {
		SymVector		ret;
		Stack<SymData>	stack;
		static auto& _r	= expr::repo();
		
		for(const Symbol& sym : input){
			switch(sym.category){
			case SymCategory::None:
			case SymCategory::Error:
				break;
			case SymCategory::Value:
				ret.push_back(sym);
				break;
			}
		}
		
		return errors::todo();
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
