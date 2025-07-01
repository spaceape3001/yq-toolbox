////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/ArgMeta.hpp>
#include <yq/meta/MetaBinder.hpp>

namespace yq {
    /*! \brief Information about an argument
    */
    template <typename T>
    class ArgMeta::Typed : public ArgMeta {
    public:
    
        //! Type of the argument
        const Meta&        type() const { return m_type; }
    
        //! Master constructor, use only if you know what you're doing
        Typed(const std::source_location& sl, Meta* parent) : 
            ArgMeta(sl, meta<T>(), parent)
        {
            m_default   = m_defaultData.pointer<T>();
        }
    };
}
