////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/meta/Meta.hpp>

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
        virtual bool            set(void*obj, const void*value) const = 0;
        /*! \brief "Sets" a property
        
            \param[out] obj     Pointer to object to set, can be null on a static object
            \param[in] value    String-form of a property
        */
        virtual bool            set(void*obj, std::string_view) const = 0;
        virtual const Meta&     data() const = 0;
        virtual const Meta&     object() const = 0;
        const PropertyInfo* property() const;
    protected:
        PropSetter(PropertyInfo*, const std::source_location& sl);
    };
}
