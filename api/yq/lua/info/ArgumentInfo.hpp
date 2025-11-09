////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/lua/types.hpp>
#include <yq/lua/info/Info.hpp>

namespace yq::lua {
    class ArgumentInfo : public Info {
    public:
    
        int             index() const { return m_index; }
        const type_t&   type() const { return m_type; }

        virtual bool   is_argument() const override { return true; }
    
    protected:
        friend class FunctionInfo;
        
        ArgumentInfo(const char* z);
        virtual ~ArgumentInfo();
    
    private:
        friend class Repo;

        type_t  m_type;
        int     m_index     = 0;
    };
}
