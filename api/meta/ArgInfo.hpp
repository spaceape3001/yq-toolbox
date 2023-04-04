////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <meta/Meta.hpp>

namespace yq {
    /*! \brief Information about an argument
    */
    class ArgInfo : public Meta {
    public:
    
        //! Type of the argument
        const Meta&         type() const { return m_type; }
        
        template <typename T> class Typed;
    
    protected:
        ArgInfo(const std::source_location& sl, const Meta&, Meta*, options_t opts);
        
    private:
        const Meta&     m_type;
        DataBlock       m_defaultData;
        const void*     m_default;
    };
}
