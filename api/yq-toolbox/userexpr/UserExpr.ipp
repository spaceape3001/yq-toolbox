////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "UserExpr.hpp"

#include <yq-toolbox/errors.hpp>
#include <yq-toolbox/basic/Any.hpp>
#include <yq-toolbox/container/Stack.hpp>
#include <yq-toolbox/text/format32.hpp>
#include <yq-toolbox/userexpr/Analysis.hpp>
#include <yq-toolbox/userexpr/Context.hpp>
#include <yq-toolbox/userexpr/impl/Compiler.hpp>
#include <yq-toolbox/userexpr/impl/Streamline.hpp>
#include <yq-toolbox/userexpr/impl/Symbol.hpp>
#include <yq-toolbox/userexpr/impl/SymData.hpp>
#include <yq-toolbox/userexpr/impl/Tokenize.hpp>
#include <yq-toolbox/userexpr/impl/VirtualMachine.hpp>

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
		m_buildError = _init(u32);
	}
	
    UserExpr::UserExpr(std::u32string_view uin)
    {
		m_buildError = _init(uin);
	}

	std::error_code    UserExpr::_init(std::u32string_view uxpr) 
	{
        std::error_code ec;
		ec	= expr::tokenize(uxpr, m_algebra);
		if(ec != std::error_code())
            return ec;
		
		ec	        = expr::streamline(m_algebra);
		if(ec != std::error_code())
            return ec;
        
        expr::Context ctx;
        expr::Analysis    analy;
        
        Ref<expr::VirtualMachine> vm  = new expr::VirtualMachine;
        
        expr::Compiler         builder(ctx, analy, vm);
        ec      = builder.compile(m_algebra);
        if(ec)
            return ec;
        m_machine       = vm;
        return {};
	}

    any_x     UserExpr::evaluate() const
    {
        expr::Context     context;
        return evaluate(context);
    }

    any_x     UserExpr::evaluate(expr::Context&ctx) const
    {
        if(!m_machine.valid())
            return errors::bad_userexpr();

        any_stack_t             values;
        std::error_code ec  =  m_machine -> execute(values, ctx);
        if(ec != std::error_code())
            return unexpected(ec);
        if(values.empty())
            return errors::empty_stack();
        if(values.size() > 1)
            return errors::mulitple_values();
        return values.pop();
    }
}


