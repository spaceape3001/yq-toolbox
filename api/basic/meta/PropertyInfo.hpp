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
    
        //! Our writer
        template <typename T> class Writer;
        
        //! Writer for statics
        template <typename T> class VarW;
        
        //! Writer for dynamics
        template <typename C, typename T> class PropW;
    
        //! Our type information
        const TypeInfo&     type() const { return m_type; }
        
        //! Gets the property/variable
        //! \param[in]  pointer Pointer to the object (can be null for statics)
        any_error_t         get(const void* obj) const;
        
        //! Write for saving
        //!
        //! \param[in]  pointer Pointer to the object (can be null for statics)
        //! \param[out]  str     Stream to write to
        std::error_code     write(const void* obj, Stream&str) const;
        
        //! Write for printing
        //!
        //! \param[in]      pointer Pointer to the object (can be null for statics)
        //! \param[in,out]  str     Stream to write to
        std::error_code     print(const void*, Stream&) const;
        
        //! Sets the property with Any
        //! \param[in,out]  pointer Pointer to the object (can be null for statics)
        //! \param[in]      value   Any value to assign to the property
        std::error_code     set(void*obj, const Any&value) const;
        
        //! Sets the property with string
        //! \param[in,out]  pointer Pointer to the object (can be null for statics)
        //! \param[in]      value   String value to assign to the property
        std::error_code     set(void*obj, std::string_view value) const;
        
        //! Our getter
        const PropGetter*   getter() const { return m_getter; }

        //! Our setter (may be NULL for read-only)
        const PropSetter*   setter() const { return m_setter; }
        
        //! TRUE if this is marked as state.
        //! 
        //! A state property is one that needs to be saved/loaded to properly recreate the object.
        bool                is_state() const;
        
        //! TRUE if this is a global/static variabels
        //!
        //! A global or static is one that lives outside a particular object, but is instead defined singularly
        //! For the entire application
        bool                is_static() const;
        
        bool                is_const() const { return flags() & CONST; }

            // best know what you're doing....
            
        /*! \brief Master Constructor 
            \note   Only use directly this if you know what you're doing, otherwise, stay away
            \param[in] zName    name of the property
            \param[in] sl       Source location of the definition (usually auto-picked up by the meta declare helpers
            \param[in] type     Data type for the property
            \param[in] parent   Parent object this is apart of
            \param[in] opts     Options
        */
        PropertyInfo(std::string_view zName, const std::source_location& sl, const TypeInfo& type, Meta* parent, options_t opts=0);
        
    private:
        const PropSetter*   m_setter    = nullptr;
        const PropGetter*   m_getter    = nullptr;
        const TypeInfo&     m_type;
        DataBlock           m_default;
    };
    
    
    
}
