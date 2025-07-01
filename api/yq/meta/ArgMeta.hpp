////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <yq/meta/Meta.hpp>
#include <yq/meta/DataBlock.hpp>

namespace yq {
    /*! \brief Information about an argument
    */
    class ArgMeta : public Meta {
    public:
    
        //! Type of the argument
        const Meta&         type() const { return m_type; }
        
        template <typename T> class Typed;
        
        const void*         default_argument() const { return m_default; }
    
    protected:
        ArgMeta(const std::source_location& sl, const Meta&, Meta*);
        
    private:
        const Meta&     m_type;
        DataBlock       m_defaultData;
        const void*     m_default   = nullptr;
    };
}
