////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/meta/Meta.hpp>

namespace yq {
    class PropertyInfo;

    /*! \brief Abstract PropGetter
        
        This is an abstract "setter" that may or may not have an object associated with it.
    */
    class PropSetter : public Meta {
    public:
    
        /*! \brief "Sets" a property
        
            \param[out] obj     Pointer to object to set, can be null on a static object
            \param[in] value    Pointer to value to use on set, assumed to match data()
        */
        virtual std::error_code set(void*obj, const void*value) const = 0;
        /*! \brief "Sets" a property
        
            \param[out] obj     Pointer to object to set, can be null on a static object
            \param[in] value    String-form of a property
        */
        virtual std::error_code set(void*obj, std::string_view) const = 0;
        
        //! Data type for the setter
        virtual const Meta&     data() const = 0;
        
        //! Object type for the setter
        virtual const Meta&     object() const = 0;
        
        //! Property info this belongs to
        const PropertyInfo* property() const;
    protected:
    
        /*! \brief Constructor
        
            \param[in] propInfo Property to attach this setter to
            \param[in] sl       Source location it's defined
        */
        PropSetter(PropertyInfo* propInfo, const std::source_location& sl);
    };
}
