////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#if 0

#include <string>
#include <string_view>
#include <0/basic/Enum.hpp>
#include <functional>
#include <0/basic/preamble.hpp>
#include <0/math/expr/preamble.hpp>
#include <0/math/expr/SymType.hpp>
#include <iosfwd>

namespace log4cpp { class CategoryStream; }

namespace yq::expr {
	
	enum class SymCategory : uint8_t {
		None	= 0,
		Error,
		Operator,
		Space,
		Text,
		Value,
		Open,
		Close,
		Special
	};
	
	enum class SymKind : uint16_t {
		None		= 0,
		
			// OPERATORS (at front to match the operators enumeration)
		YQ_OPERATORS,

			// VALUES
		Integer,
		Octal,
		Hexadecimal,
		Float,

			// TEXTS
		Variable,
		Function,
		Constant,
        Constructor,
		
			// SPECIALS
        Assign,
        Duplicate,
        Comma,
        
			// OPEN/CLOSE
		Generic,
		Array,
		Tuple
	};
	

	struct SymCode {
		SymKind		kind		= SymKind::None;
		SymCategory	category	= SymCategory::None;
		SymType		type		= SymType::None;
		
		constexpr bool operator==(const SymCode&) const = default;
	};
	
    //! Heavy weight symbol
	struct Symbol {
        SymType         	type    	= SymType::None;	// temporary until transition's done
		SymCategory			category	= {};
		SymKind				kind		= SymKind::None;
		uint8_t				extra		= 0;
		std::u32string		text;
		Any					value;
		
		constexpr bool operator==(const Symbol&) const = default;
		
		constexpr operator SymCode() const noexcept 
		{
			return { kind, category, type };
		}
	};
	
	
    //! Light weight token
    struct Token {
        SymType         type    	= SymType::None;
		SymCategory		category	= {};
		SymKind			kind		= SymKind::None;
        size_t          length     	= 0;
        
        constexpr bool  operator==(const Token&) const noexcept = default;
    };

    using TokenFN   = std::function<std::error_code(SymCode,std::u32string_view)>;
    using feature_t = std::pair<bool,size_t>;

    /*! \brief Sub-tokenizes
    
        This is the sub-tokenizer, it scans the text for what seems like the next
        relevant symbol.  
    */
    Token               token(std::u32string_view);
    

    Expect<SymVector>   tokenize(std::string_view);
    Expect<SymVector>   tokenize(std::u32string_view);

    std::error_code     tokenize(std::u32string_view, TokenFN&&);
    std::error_code     tokenize(std::string_view, TokenFN&&);
    
    log4cpp::CategoryStream&    operator<<(log4cpp::CategoryStream&, const Symbol&);
    log4cpp::CategoryStream&    operator<<(log4cpp::CategoryStream&, const Token&);
    std::ostream&    operator<<(std::ostream&, const Symbol&);
    std::ostream&    operator<<(std::ostream&, const Token&);

    std::error_code		streamline(std::vector<Symbol>&);
    
    Expect<SymVector>	compile_rpn(const SymVector&);

    constexpr bool		is_comma(const Symbol&sym)
    {
		return (sym.category == SymCategory::Special) && (sym.kind == SymKind::Comma);
	}

    constexpr bool		is_comma(const SymCode&sym)
    {
		return (sym.category == SymCategory::Special) && (sym.kind == SymKind::Comma);
	}
}
#endif
