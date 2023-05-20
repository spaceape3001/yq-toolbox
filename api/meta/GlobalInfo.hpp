////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <meta/Meta.hpp>
#include <meta/InfoBinder.hpp>
#include <meta/CompoundInfo.hpp>

namespace yq {

    //! \brief Global "CLASS"
    //! 
    //! \note this class is here for the API meta binding, not subsequently used, call namespace
    class Global { };
    
    class GlobalInfo : public CompoundInfo {
    public:
        
        template <typename> class Writer;   // which will only ever by GlobalInfo...however, consistency
        
        static GlobalInfo&          instance();

        const LUC<MethodInfo>&      methods() const { return m_methods; }
        const LUC<PropertyInfo>&    properties() const { return m_properties; }
        

    protected:
        GlobalInfo(const std::source_location& sl = std::source_location::current());
        virtual void                sweep_impl() override;

        friend class PropertyInfo;
        friend class MethodInfo;

        
        //! Lookup/Container for the methods
        LUC<MethodInfo>         m_methods;
        
        //! Lookup/Container for the properties
        LUC<PropertyInfo>       m_properties;

    };
    
    template <>
    struct InfoBinder<Global>  {
        using Info  = GlobalInfo;
        static constexpr const bool     Defined     = true;
        static constexpr const bool     IsCompound  = true;     
        static constexpr const bool     IsType      = false;
        static constexpr const bool     IsObject    = false;
        static const GlobalInfo&        bind();
        static GlobalInfo&              edit();
    };
    
    inline GlobalInfo*  to_global(Meta*m)
    {
        return (m && (m->flags() & GLOBAL)) ? static_cast<GlobalInfo*>(m) : nullptr;
    }
    
    inline const GlobalInfo*  to_global(const Meta*m)
    {
        return (m && (m->flags() & GLOBAL)) ? static_cast<const GlobalInfo*>(m) : nullptr;
    }
}
