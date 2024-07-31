////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Repo.hpp"
#include <0/basic/errors.hpp>
#include <0/basic/TextUtils.hpp>
#include <0/basic/TextUtils32.hpp>


namespace yq::expr {
    enum : uint8_t {
        PCompare    = 1,
        PLogic,
        PAddSub,
        PMulDiv,
        PPower
    };
    
    // Table of known operators (this *WILL* grow)
    const OpData             Repo::kStandardOperators[] = {
        { 
			.text 		= U",",  
			.type		= OperatorType::Comma,
			.category 	= SymCategory::Special,
			.kind		= SymKind::Comma
		},
        { 
			.text 		= U":=", 
			.type 		= OperatorType::Set, 
			.category 	= SymCategory::Special,
			.kind		= SymKind::Assign,
			.self 		= true 
		},
		{ 
			.text 		= U"+",  
			.code		= Operator::Add,        
			.type		= OperatorType::Binary, 
			.category	= SymCategory::Operator,
			.kind		= SymKind::Add,
			.priority	= PAddSub 
		},
        { 
			.text 		= U"-",  
			.code 		= Operator::Subtract,   
			.type		= OperatorType::Binary, 
			.category	= SymCategory::Operator,
			.kind		= SymKind::Subtract,
			.priority   = PAddSub 
		},
        { 
			.text 		= U"*",  
			.code		= Operator::Multiply,   
			.type		= OperatorType::Binary, 
			.category	= SymCategory::Operator,
			.kind		= SymKind::Multiply,
			.priority	= PMulDiv 
		},
        { 
			.text 		= U"/",  
			.code		= Operator::Divide,     
			.type		= OperatorType::Binary, 
			.category	= SymCategory::Operator,
			.kind		= SymKind::Divide,
			.priority	= PMulDiv 
		},
        { 
			.text 		= U"^",  
			.code		= Operator::Power,      
			.type		= OperatorType::Binary, 
			.category	= SymCategory::Operator,
			.kind		= SymKind::Power,
			.priority 	= PPower 
		},
        { 
			.text 		= U"⊗",  
			.code 		= Operator::TensorProduct, 
			.type		= OperatorType::Binary, 
			.category	= SymCategory::Operator,
			.kind		= SymKind::TensorProduct,
			.priority	= PMulDiv 
		},
        { 
			.text 		= U"√",  
			.code		= Operator::SquareRoot, 
			.type		= OperatorType::Left, 
			.category	= SymCategory::Operator,
			.kind		= SymKind::SquareRoot,
			.priority	= PPower 
		},
        { 
			.text 		= U"∛",  
			.code		= Operator::CubeRoot,   
			.type		= OperatorType::Left, 
			.category	= SymCategory::Operator,
			.kind		= SymKind::CubeRoot,
			.priority	= PPower 
		},
        { 
			.text 		= U"∜",  
			.code 		= Operator::FourthRoot, 
			.type		= OperatorType::Left, 
			.category	= SymCategory::Operator,
			.kind		= SymKind::FourthRoot,
			.priority	= PPower 
		},
        { 
			.text 		= U"!=", 
			.code		= Operator::NotEqual, 
			.type		= OperatorType::Binary, 
			.category	= SymCategory::Operator,
			.kind		= SymKind::NotEqual,
			.priority	= PCompare 
		},
        { 
			.text 		= U"<>", 
			.code		= Operator::NotEqual, 
			.type 		= OperatorType::Binary, 
			.category	= SymCategory::Operator,
			.kind		= SymKind::NotEqual,
			.priority	= PCompare 
		},
        { 
			.text 		= U"≠",  
			.code 		= Operator::NotEqual, 
			.type		= OperatorType::Binary, 
			.category	= SymCategory::Operator,
			.kind		= SymKind::NotEqual,
			.priority	= PCompare 
		},
        { 
			.text 		= U"<",  
			.code		= Operator::Less, 
			.type		= OperatorType::Binary, 
			.category	= SymCategory::Operator,
			.kind		= SymKind::NotEqual,
			.priority	= PCompare 
		},
        { 
			.text 		= U"<=", 
			.code 		= Operator::LessEqual, 
			.type		= OperatorType::Binary, 
			.category	= SymCategory::Operator,
			.kind		= SymKind::LessEqual,
			.priority 	= PCompare 
		},
        { 
			.text 		= U"≤",  
			.code		= Operator::LessEqual, 
			.type		= OperatorType::Binary, 
			.category	= SymCategory::Operator,
			.kind		= SymKind::LessEqual,
			.priority	= PCompare 
		},
        { 
			.text 		= U">",  
			.code		= Operator::Greater, 
			.type		= OperatorType::Binary, 
			.category	= SymCategory::Operator,
			.priority	= PCompare 
		},
        { 
			.text 		= U">=", 
			.code		= Operator::GreaterEqual, 
			.type		= OperatorType::Binary, 
			.category	= SymCategory::Operator,
			.priority	= PCompare 
		},
        { 
			.text 		= U"≥",  
			.code		= Operator::GreaterEqual, 
			.type		= OperatorType::Binary, 
			.category	= SymCategory::Operator,
			.priority	= PCompare 
		},
        { 
			.text 		= U"(",  
			.type 		= OperatorType::Open, 
			.category	= SymCategory::Open,
			.kind		= SymKind::Generic,
			.other 		= U")" 
		},
        { 
			.text 		= U")",  
			.type 		= OperatorType::Close, 
			.category	= SymCategory::Close,
			.kind		= SymKind::Generic,
			.other 		= U"(" 
		},
        { 
			.text 		= U"[",  
			.type 		= OperatorType::Open, 
			.category	= SymCategory::Open,
			.kind		= SymKind::Array,
			.other 		= U"]" 
		},
        { 
			.text 		= U"]",  
			.type 		= OperatorType::Close, 
			.category	= SymCategory::Close,
			.kind		= SymKind::Array,
			.other 		= U"[" 
		},
        { 
			.text 		= U"{",  
			.type 		= OperatorType::Open, 
			.category	= SymCategory::Open,
			.kind		= SymKind::Tuple,
			.other 		= U"}" 
		},
        { 
			.text 		= U"}",  
			.type 		= OperatorType::Close, 
			.category	= SymCategory::Close,
			.kind		= SymKind::Tuple,
			.other 		= U"{" 
		}
    };

    Repo& Repo::instance()
    {   
        static Repo *s_repo = new Repo;
        return *s_repo;
    }
    
    Repo::Repo() : CompoundInfo("yq::expr::Repo", std::source_location::current())
    {
        m_constants[U"pi"]     = std::numbers::pi_v<double>;
        m_constants[U"sqrt2"]  = std::numbers::sqrt2_v<double>;
        m_constants[U"sqrt3"]  = std::numbers::sqrt3_v<double>;
        m_constants[U"e"]      = std::numbers::e_v<double>;
        m_constants[U"ln2"]    = std::numbers::ln2_v<double>;
        m_constants[U"ln10"]   = std::numbers::ln10_v<double>;
        m_constants[U"egamma"] = std::numbers::egamma_v<double>;
        m_punctText.insert(U'_');

        for(const OpData& d : kStandardOperators){
            m_operators[d.text] = &d;
        }
    }
    
    Repo::~Repo()
    {
    }
    
    void    Repo::sweep_impl()
    {
        for(const Meta* m : children()){
            if(m && m->has(Flag::METHOD)){
                m_functions << static_cast<const MethodInfo*>(m);
            }
            if(m && m->has(Flag::PROPERTY)){
                m_variables << static_cast<const PropertyInfo*>(m);
            }
        }
    }
    
    Expect<Any>     Repo::constant(std::string_view k) const
    {
        std::u32string  k32 = to_u32string(k);
        return constant(k32);
    }
    
    Expect<Any>     Repo::constant(std::u32string_view k) const
    {
        auto i = m_constants.find(std::u32string(k));
        if(i != m_constants.end())
            return i->second;
        return errors::bad_argument();
    }

    bool            Repo::has_constant(std::string_view k) const
    {
        std::u32string  k32 = to_u32string(k);
        return has_constant(k32);
    }
    
    bool            Repo::has_constant(std::u32string_view k) const
    {
        return m_constants.contains(std::u32string(k));
    }

    bool            Repo::has_function(std::string_view k) const
    {
        return m_functions.lut.contains(k);
    }
    
    bool            Repo::has_function(std::u32string_view k) const
    {
        return m_functions.lut32.contains(k);
    }

    bool            Repo::has_operator(std::string_view k) const
    {
        std::u32string  k32 = to_u32string(k);
        return m_operators.contains(k32);
    }

    bool            Repo::has_operator(std::u32string_view k) const
    {
        return m_operators.contains(k);
    }
    
    bool            Repo::has_variable(std::string_view k) const
    {
        return m_variables.lut.contains(k);
    }
    
    bool            Repo::has_variable(std::u32string_view k) const
    {
        return m_variables.lut32.contains(k);
    }

    bool            Repo::is_punct_text(char32_t ch) const
    {
        return m_punctText.contains(ch);
    }

	const OpData*	Repo::operator_(std::u32string_view k) const
	{
		auto itr = m_operators.find(k);
		if(itr != m_operators.end())
			return (itr->second);
		return nullptr;
	}

    Expect<Any>     Repo::variable(std::string_view k) const
    {
        auto i = m_variables.lut.find(k);
        if(i != m_variables.lut.end() && i->second)
            return i->second->get(nullptr);
        return errors::bad_argument();
    }
    
    Expect<Any>     Repo::variable(std::u32string_view k) const
    {
        auto i = m_variables.lut32.find(k);
        if(i != m_variables.lut32.end() && i->second)
            return i->second->get(nullptr);
        return errors::bad_argument();
    }
    
}
