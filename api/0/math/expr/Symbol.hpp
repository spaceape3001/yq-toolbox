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
	struct Symbol {
		string_t    text;
		SymCategory	category	= SymCategory::None;
		SymKind		kind		= SymKind::None;
		
		constexpr bool operator==(const Symbol&) const = default;

		constexpr operator SymCode() const noexcept;
	};

	struct SymCode {
		SymCategory	category	= SymCategory::None;
		SymKind		kind		= SymKind::None;
		
		constexpr bool operator==(const SymCode&) const = default;
	};

	constexpr Symbol::operator SymCode() const noexcept 
	{
		return { .category=category, .kind=kind };
	}

    constexpr bool	is_comma(const SymCode&sym)
    {
        return (sym.category == SymCategory::Special) && (sym.kind == SymKind::Comma);
    }

    constexpr bool is_starting_term(const SymCode& sc)
    {
        if(sc == SymCode{})
            return true;
        if(sc.category == SymCategory::Open)
            return true;
        if(sc.category == SymCategory::Operator)
            return true;
        if(is_comma(sc))
            return true;
        return false;
    }
    
    constexpr bool is_ending_term(const SymCode& sc)
    {
        if(sc == SymCode{})
            return true;
        if(sc.category == SymCategory::Close)
            return true;
        if(sc.category == SymCategory::Operator)
            return true;
        if(is_comma(sc))
            return true;
        return false;
    }
        
    log4cpp::CategoryStream&    operator<<(log4cpp::CategoryStream&, const Symbol&);
    log4cpp::CategoryStream&    operator<<(log4cpp::CategoryStream&, const SymVector&);
    std::ostream&    operator<<(std::ostream&, const Symbol&);
    std::ostream&    operator<<(std::ostream&, const SymVector&);
}
