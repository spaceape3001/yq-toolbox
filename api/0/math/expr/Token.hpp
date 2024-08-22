////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/math/expr/preamble.hpp>
#include <0/math/expr/SymCategory.hpp>
#include <0/math/expr/SymKind.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq::expr {
    //! Light weight token
    struct Token {
		SymCategory	category	= SymCategory::None;
		SymKind		kind		= SymKind::None;
        size_t      length     	= 0;
        
        constexpr bool  operator==(const Token&) const noexcept = default;
    };

    log4cpp::CategoryStream&    operator<<(log4cpp::CategoryStream&, const Token&);
    std::ostream&               operator<<(std::ostream&, const Token&);
}