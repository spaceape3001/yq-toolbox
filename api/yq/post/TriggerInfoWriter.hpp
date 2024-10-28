////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/post/Trigger.hpp>
#include <yq/post/FilterInfoWriter.hpp>

namespace yq::post {

    namespace impl {

        template <SomeTrigger T, SomePost P> 
        struct TriggerArgDeducer {
            using trigger_t     = T;
            using post_t        = P;
        };
        
        template <SomeTrigger T, SomePost P> 
        constexpr TriggerArgDeducer<T,P> deduce_trigger(bool (T::*)(const P&)) 
        {
            return {};
        }
        
        struct AbstractTriggerTraits {
            using post_t        = void;
            static constexpr bool  has_accept  = false;
        };
        
        template <SomeTrigger T>
        struct ConcreteTriggerTraits {
            using deduce_t          = decltype(deduce_trigger(&T::accept));
            using post_t            = typename deduce_t::post_t;
            static_assert( std::derived_from<post_t, Post>, "Post must be post-based class!");
            static constexpr bool has_accept  = true;
        };
    }

    
    template <typename C>
    class Trigger::Fixer : public ObjectFixer<C> {
    public:
        using traits_t      = std::conditional_t<HasAccept<C>, impl::ConcreteTriggerTraits<C>, impl::AbstractTriggerTraits>;
        using post_t        = typename traits_t::post_t;
        static constexpr bool      has_accept  = traits_t::has_accept;
        
        Fixer(std::string_view zName, const typename C::MyBase::MyInfo& base, const std::source_location& sl=std::source_location::current()) : 
            ObjectFixer<C>(zName, base, sl)
        {
            if constexpr (has_accept){
                if constexpr (!std::is_same_v<post_t, Post>){
                    TriggerInfo::m_postInfo  = &meta<post_t>();
                }
            } else {
                Meta::set(Meta::Flag::ABSTRACT);
            }
        }
        
        FilterResult      accept(const Trigger& trigger, const Post& thePost) const override
        {
            if constexpr (has_accept){
                MismatchFlags    m;
                const post_t*       pp;
                
                if constexpr (std::is_same_v<post_t, Post>){
                    pp      = &thePost;
                }
                if constexpr (!std::is_same_v<post_t, Post>){
                    pp      = dynamic_cast<const post_t*>(&thePost);
                    if(!pp)
                        m |= MismatchType::InPost;
                }
                
                if(m != MismatchFlags())
                    return m;
                
                return static_cast<const C&>(trigger).accept(*pp);
            } 
            if constexpr (!has_accept){
                return MismatchFlags(ALL);
            }
        }

        FilterResult      accept(const Filter& filter, const Dispatcher&, const Dispatcher&, const Post& thePost) const override
        {
            return Fixer<C>::accept(static_cast<const Trigger&>(filter), thePost);
        }
    };
    
    /*! \brief Writer of event information
    */
    template <typename C>
    class TriggerInfo::Writer : public FilterInfo::Writer<C> {
    public:
    
        //! Constructor of widget info (this is used by derived classes and this classes other constructor)
        Writer(TriggerInfo* pInfo) : FilterInfo::Writer<C>(pInfo), m_meta(pInfo)
        {
        }
        
        //! Constructor of widget info (this is used by the writer<T>() methods)
        Writer(TriggerInfo& pInfo) : Writer(&pInfo)
        {
        }

    private:
        TriggerInfo* m_meta;
    };
}
