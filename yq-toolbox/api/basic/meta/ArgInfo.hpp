////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <basic/meta/Meta.hpp>

namespace yq {
    /*! \brief Information about an argument
    */
    class ArgInfo : public Meta {
    public:
    
        const Meta&        type() const { return m_type; }
    
    private:
        ArgInfo(std::string_view zName, const std::source_location& sl, const Meta&, Meta*);
        
        const Meta&             m_type;
        DataBlock               m_default;
    };
}
