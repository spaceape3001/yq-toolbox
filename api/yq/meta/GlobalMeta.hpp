////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/Meta.hpp>
#include <yq/meta/MetaBinder.hpp>
#include <yq/meta/CompoundMeta.hpp>
#include <yq/meta/MetaLookup.hpp>
#include <yq/meta/MethodMeta.hpp>

namespace yq {

    //! \brief Global "CLASS"
    //! 
    //! \note this class is here for the API meta binding, not subsequently used, call namespace
    class Global { };
    
    class GlobalMeta : public CompoundMeta {
    public:
        
        template <typename> class Writer;   // which will only ever by GlobalMeta...however, consistency
        
        static GlobalMeta&          instance();

        const MetaLookup<MethodMeta>&    methods() const { return m_methods; }
        const MetaLookup<PropertyMeta>&  properties() const { return m_properties; }
        
        template <typename Pred>
        auto                        all_functions(std::string_view k, Pred pred) const;

    protected:
        GlobalMeta(std::string_view name="Global", const std::source_location& sl = std::source_location::current());
        virtual void                sweep_impl() override;

        friend class PropertyMeta;
        friend class MethodMeta;

        
        //! Lookup/Container for the methods
        MetaLookup<MethodMeta>         m_methods;
        
        //! Lookup/Container for the properties
        MetaLookup<PropertyMeta>       m_properties;

    };

    template <typename Pred>
    auto    GlobalMeta::all_functions(std::string_view k, Pred pred) const
    {
        using pred_result_t = decltype(pred((const MethodMeta*) nullptr));
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
    struct MetaBinder<Global>  {
        using Info  = GlobalMeta;
        static constexpr const bool     Defined     = true;
        static constexpr const bool     IsCompound  = true;     
        static constexpr const bool     IsType      = false;
        static constexpr const bool     IsObject    = false;
        static const GlobalMeta&        bind();
        static GlobalMeta&              edit();
    };
    
    GlobalMeta*  to_global(Meta*);
    
    const GlobalMeta*  to_global(const Meta*m);
}

