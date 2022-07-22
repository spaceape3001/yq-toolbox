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
    
        const auto&             methods() const { return m_methods; }
        const auto&             properties() const { return m_properties; }
    
    protected:
        friend class Global;
        
        LUC<MethodInfo>         m_methods;
        LUC<PropertyInfo>       m_properties;
        
        CompoundInfo(std::string_view zName, const std::source_location& sl, Meta* par=nullptr, id_t i=AUTO_ID);
        ~CompoundInfo();

        virtual void            sweep_impl() override;
        
        void        gather(LUC<MethodInfo>&);
        void        gather(LUC<PropertyInfo>&);

    };
}
