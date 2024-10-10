////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/ArgInfo.hpp>
#include <yq/meta/InfoBinder.hpp>

namespace yq {
    /*! \brief Information about an argument
    */
    template <typename T>
    class ArgInfo::Typed : public ArgInfo {
    public:
    
        //! Type of the argument
        const Meta&        type() const { return m_type; }
    
        //! Master constructor, use only if you know what you're doing
        Typed(const std::source_location& sl, Meta* parent) : 
            ArgInfo(sl, meta<T>(), parent)
        {
            m_default   = m_defaultData.pointer<T>();
        }
    };
}
