////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <basic/meta/Meta.hpp>

namespace yq {

    class PropGetter;
    class PropSetter;
    class Stream;

    /*! \brief Attribute of a object/value
    
        A property is an attribute of an object/value.  
        A "state" proeprty is considered to be a field of a structure.  
        If all states are restored, the objects/value should behave identical.  
        Non-state proproperties should generally be read-only, but not always the case.  
        A vector's "set-heading" is an equally valid way to set a vector -- though that could also
        be in a method (or static method);
        
    */
    class PropertyInfo : public Meta {
        friend class PropGetter;
        friend class PropSetter;
    public:
    
        template <typename T> class Writer;
        template <typename T> class VarW;
        template <typename C, typename T> class PropW;
    
        const TypeInfo&     type() const { return m_type; }
        
        Any                 get(const void*) const;
        
        // write for saving
        bool                write(const void*, Stream&) const;
        
        // write for printing
        bool                print(const void*, Stream&) const;
        
        bool                set(void*, const Any&) const;
        bool                set(void*, std::string_view) const;
        
        const PropGetter*   getter() const { return m_getter; }
        const PropSetter*   setter() const { return m_setter; }
        
        bool                is_state() const;
        bool                is_static() const;

            // best know what you're doing....
        PropertyInfo(std::string_view zName, const std::source_location& sl, const TypeInfo&, Meta*, options_t opts=0);
        
    private:
        const PropSetter*   m_setter    = nullptr;
        const PropGetter*   m_getter    = nullptr;
        const TypeInfo&     m_type;
        DataBlock           m_default;
    };
    
    
    
}
