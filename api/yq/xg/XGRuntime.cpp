////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "XGRuntime.hpp"
#include <yq/errors.hpp>
#include <yq/xg/logging.hpp>
#include <yq/xg/XGElement.hpp>

namespace yq {
    XGRuntime::XGRuntime()
    {
    }
    
    XGRuntime::~XGRuntime()
    {
        kill();
    }
    
    XGRuntime::XGRuntime(GGraph g)
    {
        std::error_code ec  = initialize(g);
        if(ec != std::error_code())
            xgError << "Cannot initialize graph: " << ec.message();
    }
    

    std::error_code             XGRuntime::add(GGraph)
    {
        return errors::todo();
    }
    
    std::error_code             XGRuntime::add(int, GGraph)
    {
        return errors::todo();
    }
    
    std::error_code             XGRuntime::add(const std::string&, GGraph)
    {
        return errors::todo();
    }

    XGElement*                  XGRuntime::element(const xg_cursor_t&k)
    {
        return m_elements.get(k, nullptr);
    }
    
    const XGElement*            XGRuntime::element(const xg_cursor_t&k) const
    {
        return m_elements.get(k, nullptr);
    }

    std::error_code XGRuntime::initialize(GGraph)
    {
        return errors::todo();
    }
    
    void                        XGRuntime::kill()
    {
        m_results.clear();
        for(auto& itr : m_elements){
            if(itr.second)
                delete itr.second;
        }
        m_elements.clear();
        m_files.clear();
        //  Roles/alts/etc...
        
        m_primary   = 0ULL;
        
    }

    GGraph                      XGRuntime::primary() const
    {
        if(auto itr = m_files.find(m_primary); itr != m_files.end())
            return itr->second.graph;
        return {};
    }

    const xg_result_t&          XGRuntime::result(const xg_cursor_t&k) const
    {
        static const xg_result_t    s_null_result;
        auto itr = m_results.find(k);
        if(itr != m_results.end())
            return itr->second;
        return s_null_result;
    }
    
    
    bool                        XGRuntime::valid() const
    {
        return m_primary != 0ULL;
    }
    
}
