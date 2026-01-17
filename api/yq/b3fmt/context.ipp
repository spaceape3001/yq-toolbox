////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "context.hpp"

namespace yq::b3::parse {
    static thread_local const context_t*    s_context   = nullptr;

    std::string_view    context_t::color(const std::string& k) const
    {
        auto i = m_colors.find(k);
        if(i == m_colors.end())
            return k;
        return i->second;
    }
    
    double              context_t::unit(const std::string& k) const
    {
        auto i = m_units.find(k);
        if(i == m_units.end())
            return 1.;
        return i->second;
    }

    const context_t*  context_t::current(const context_t*p)
    {
        std::swap(p, s_context);
        return p;
    }
    
    
    const context_t*  context_t::current()
    {
        return s_context;
    }
}
