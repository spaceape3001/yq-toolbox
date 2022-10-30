////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <basic/meta/MethodInfo.hpp>
#include <basic/meta/PropertyInfo.hpp>

namespace yq {

    /*! \brief Intermediate Meta that can have methods/properties.  
    
        This is here to facilitate sharing method/properties between both types & objects & global.
    
    */
    class CompoundInfo : public Meta {
    public:

        class Static;

        template <typename C> class Dynamic;
    
        //! All methods for this info
        const auto&             methods() const { return m_methods; }
        
        //! All properties
        const auto&             properties() const { return m_properties; }
    
    protected:
        friend class Global;
        
        //! Lookup/Container for the methods
        LUC<MethodInfo>         m_methods;
        
        //! Lookup/Container for the properties
        LUC<PropertyInfo>       m_properties;
        
        //! Constructor
        //! \param[in] zName    The name of the object
        //! \param[in] sl       Source location of declaration
        //! \param[in] par      Parent meta
        //! \param[in] i        Initial ID
        CompoundInfo(std::string_view zName, const std::source_location& sl, Meta* par=nullptr, id_t i=AUTO_ID);
        
        //! Destructor
        ~CompoundInfo();

        //! Implementation of the sweep step
        virtual void            sweep_impl() override;
        
        //! Used to gather the methods from the children meta
        void        gather(LUC<MethodInfo>&);

        //! Used to gather the properties from the children meta
        void        gather(LUC<PropertyInfo>&);

    };
}
