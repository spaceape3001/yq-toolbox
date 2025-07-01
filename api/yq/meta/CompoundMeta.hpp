////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <yq/meta/MethodMeta.hpp>
#include <yq/meta/PropertyMeta.hpp>

namespace yq {

    /*! \brief Intermediate Meta that can have methods/properties.  
    
        This is here to facilitate sharing method/properties between both types & objects & global.
    
    */
    class CompoundMeta : public Meta {
    public:

        class Static;

        template <typename C> class Dynamic;

    protected:
        
        //! Constructor
        //! \param[in] zName    The name of the object
        //! \param[in] sl       Source location of declaration
        //! \param[in] par      Parent meta
        //! \param[in] i        Initial ID
        CompoundMeta(std::string_view zName, const std::source_location& sl, Meta* par=nullptr, id_t i=AUTO_ID);
        
        //! Destructor
        ~CompoundMeta();

        //! Implementation of the sweep step
        virtual void            sweep_impl() override;
        
        //! Used to gather the methods from the children meta
        void        gather(MetaLookup<MethodMeta>&);

        //! Used to gather the properties from the children meta
        void        gather(MetaLookup<PropertyMeta>&);
        

    };
}
