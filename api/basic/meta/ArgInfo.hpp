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
    
        //! Type of the argument
        const Meta&         type() const { return m_type; }
        
        template <typename T> class Typed;
    
    private:
        ArgInfo(const std::source_location& sl, const Meta&, Meta*);

        const Meta&     m_type;
        DataBlock       m_defaultData;
        const void*     m_default;
    };
}
