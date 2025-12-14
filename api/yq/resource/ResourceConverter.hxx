////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/resource/ResourceConverter.hpp>
#include <type_traits>

namespace yq {
    template <SomeResource S, SomeResource T, typename Pred>
    class TypedResourceConverter : public ResourceConverter {
    public:
        //using Pred    = std::function<T*(const S&)>;
    
        TypedResourceConverter(Pred&&fn, const std::source_location& sl) : 
            ResourceConverter(meta<S>(), meta<T>(), sl), m_function(std::move(fn))
        {
        }
        
        ResourcePtr convert(const Resource& resource) const override
        {
            const S*    s   = dynamic_cast<const S*>(&resource);
            if(!s)
                return {};
                
            if constexpr (std::is_invocable_r_v<Ref<T>, Pred, const S&>){
                return m_function(*s).ptr();
            } else if constexpr (std::is_invocable_r_v<T*, Pred, const Ref<const S>&>){
                return m_function(s);
            } else if constexpr (std::is_invocable_r_v<T*, Pred, const S&>){
                return m_function(*s);
            } else if constexpr (std::is_invocable_r_v<T*, Pred, const Ref<const S>&>){
                return m_function(s);
            } else {
                return {};
            }
        }

    private:
        Pred          m_function;
    };
}
