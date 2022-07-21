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
        
        This is an abstract "getter" that may or may not have an object associated with it.
    */
    class PropGetter : public Meta {
    public:
    
        /*! \brief "Gets" the value for the meta
        
            \param[out] dst     Pointer to destination, assumed to be correct buffer.
            \param[in] obj      Pointer to the object, if used.  (Ignored on static properties.)
        */
        virtual bool            get(void*dst, const void*obj) const = 0;
        
        /*! \brief "Streams" the value for the meta (writing)
        
            \param[out] dst     Stream destination, assumed to be correct buffer.
            \param[in] obj      Pointer to the object, if used.  (Ignored on static properties.)
        */
        virtual bool            write(Stream&, const void*) const = 0;

        /*! \brief "Streams" the value for the meta (printing)
        
            \param[out] dst     Stream destination, assumed to be correct buffer.
            \param[in] obj      Pointer to the object, if used.  (Ignored on static properties.)
        */
        virtual bool            print(Stream&, const void*) const = 0;

        /*! \brief Object/Type meta type expected for src
        
            \note This will be invalid() for static properties.
        */
        virtual const Meta&     object() const = 0;
        
        /*! \brief Object/Type for the data
        */
        virtual const Meta&     data() const = 0;
        
        /*! \brief Property this is associated with.
        */
        const PropertyInfo* property() const;

    protected:
        PropGetter(PropertyInfo*, const std::source_location& sl);
    };
    
}
