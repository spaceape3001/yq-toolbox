////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/meta/Meta.hpp>
#include <0/meta/InfoBinder.hpp>
#include <0/meta/CompoundInfo.hpp>
#include <0/meta/MethodInfo.hpp>

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
        
        template <typename Pred>
        auto                        all_functions(std::string_view k, Pred pred) const;

    protected:
        GlobalInfo(std::string_view name="Global", const std::source_location& sl = std::source_location::current());
        virtual void                sweep_impl() override;

        friend class PropertyInfo;
        friend class MethodInfo;

        
        //! Lookup/Container for the methods
        LUC<MethodInfo>         m_methods;
        
        //! Lookup/Container for the properties
        LUC<PropertyInfo>       m_properties;

    };

    template <typename Pred>
    auto    GlobalInfo::all_functions(std::string_view k, Pred pred) const
    {
        using pred_result_t = decltype(pred((const MethodInfo*) nullptr));
        if constexpr (!std::is_same_v<pred_result_t, void>){
            auto R  = m_methods.lut.equal_range(k);
            for(auto r = R.first; r!=R.second; ++r){
                if(!r->second)
                    continue;
                pred_result_t   tmp = pred(r->second);
                if(tmp != pred_result_t{})
                    return tmp;
            }
            return pred_result_t{};
        } else if constexpr (std::is_same_v<pred_result_t, void>){
            auto R  = m_methods.lut.equal_range(k);
            for(auto r = R.first; r!=R.second; ++r){
                if(!r->second)
                    continue;
                pred(r->second);
            }
            return;
        }
    }
    
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
    
    GlobalInfo*  to_global(Meta*);
    
    const GlobalInfo*  to_global(const Meta*m);
}

