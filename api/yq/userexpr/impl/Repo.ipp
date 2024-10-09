////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq/userexpr/impl/Repo.hpp>

namespace yq::expr {
    Repo& Repo::instance()
    {   
        static Repo *s_repo = new Repo;
        return *s_repo;
    }
    
    Repo::Repo() : CompoundInfo("yq::expr::Repo", std::source_location::current())
    {
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
    
    any_x     Repo::constant(std::string_view k) const
    {
        std::u32string  k32 = to_u32string(k);
        return constant(k32);
    }
    
    any_x     Repo::constant(std::u32string_view k) const
    {
        auto i = m_constants.find(std::u32string(k));
        if(i != m_constants.end())
            return i->second;
        return errors::bad_argument();
    }

    const TypeInfo* Repo::constant_type(string_view_t k) const
    {
        auto i = m_constants.find(string_t(k));
        if(i != m_constants.end())
            return &(i->second.type());
        return nullptr;
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
			return &(itr->second);
		return nullptr;
	}

    any_x     Repo::variable(std::string_view k) const
    {
        auto i = m_variables.lut.find(k);
        if(i != m_variables.lut.end() && i->second)
            return i->second->get(nullptr);
        return errors::bad_argument();
    }
    
    any_x     Repo::variable(std::u32string_view k) const
    {
        auto i = m_variables.lut32.find(k);
        if(i != m_variables.lut32.end() && i->second)
            return i->second->get(nullptr);
        return errors::bad_argument();
    }
    

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Repo&   repo() 
    {   
        return Repo::instance();
    }

}

namespace yq {
    const expr::Repo&        InfoBinder<expr::Repo>::bind()
    {
        return expr::Repo::instance();
    }
    
    expr::Repo&       InfoBinder<expr::Repo>::edit()
    {
        return expr::Repo::instance();
    }
}
