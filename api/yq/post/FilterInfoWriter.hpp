////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/post/Dispatcher.hpp>
#include <yq/post/Filter.hpp>
#include <yq/post/Post.hpp>
#include <yq/meta/ObjectInfoWriter.hpp>

namespace yq::post {
    
    template <typename T>
    concept HasAccept  = requires {
        { T::accept };
    };

    namespace impl {

        template <SomeFilter F, SomeDispatcher S, SomeDispatcher R, SomePost P> 
        struct FilterArgDeducer {
            using filter_t      = F;
            using sender_t      = S;
            using receiver_t    = R;
            using post_t        = P;
        };
        
        template <SomeFilter F, SomeDispatcher S, SomeDispatcher R, SomePost P> 
        constexpr FilterArgDeducer<F,S,R,P> deduce_filter(bool (F::*)(const S&, const R&, const P&)) 
        {
            return {};
        }
        
        struct AbstractFilterTraits {
            using sender_t      = void;
            using receiver_t    = void;
            using post_t        = void;
            static constexpr bool  has_accept  = false;
        };
        
        template <SomeFilter F> 
        struct ConcreteFilterTraits {
            using deduce_t          = decltype(deduce_filter(&F::accept));
            using sender_t          = typename deduce_t::sender_t;
            using receiver_t        = typename deduce_t::receiver_t;
            using post_t            = typename deduce_t::post_t;

            static_assert( std::derived_from<sender_t, Dispatcher>, "Sender must be dispatcher based!");
            static_assert( std::derived_from<receiver_t, Dispatcher>, "Receiver must be dispatcher based!");
            static_assert( std::derived_from<post_t, Post>, "Post must be post-based class!");

            static constexpr bool has_accept  = true;
        };
    }
    
    
    template <typename C>
    class Filter::Fixer : public ObjectFixer<C> {
    public:
    
        using traits_t      = std::conditional_t<HasAccept<C>, impl::ConcreteFilterTraits<C>, impl::AbstractFilterTraits>;
        using sender_t      = typename traits_t::sender_t;
        using receiver_t    = typename traits_t::receiver_t;
        using post_t        = typename traits_t::post_t;
        static constexpr bool      has_accept  = traits_t::has_accept;
        
        Fixer(std::string_view zName, const typename C::MyBase::MyInfo& base, const std::source_location& sl=std::source_location::current()) : 
            ObjectFixer<C>(zName, base, sl)
        {
            if constexpr (has_accept){
                if constexpr (is_object_v<sender_t>){
                    FilterInfo::m_sender    = &meta_unsafe<sender_t>();
                }
                if constexpr (is_object_v<receiver_t>){
                    FilterInfo::m_receiver  = &meta_unsafe<receiver_t>();
                }
                if constexpr (!std::is_same_v<post_t, Post>){
                    FilterInfo::m_postInfo  = &meta<post_t>();
                }
            } else {
                Meta::set(Meta::Flag::ABSTRACT);
            }
        }
        
        FilterResult      accept(const Filter& filter, const Dispatcher& sender, const Dispatcher&recipient, const Post& thePost) const override
        {
            if constexpr (has_accept){
                MismatchFlags    m;
            
                const sender_t*     tx;
                const receiver_t*   rx;
                const post_t*       pp;
                
                if constexpr (std::is_same_v<sender_t, Dispatcher>){
                    tx      = &sender;
                }
                if constexpr (!std::is_same_v<sender_t, Dispatcher>){
                    tx      = dynamic_cast<const sender_t*>(&sender);
                    if(!tx)
                        m |= MismatchType::InSender;
                }
                if constexpr (std::is_same_v<receiver_t, Dispatcher>){
                    rx      = &recipient;
                }
                if constexpr (!std::is_same_v<receiver_t, Dispatcher>){
                    rx      = dynamic_cast<const receiver_t*>(&recipient);
                    if(!tx)
                        m |= MismatchType::InReceiver;
                }
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

                return static_cast<const C&>(filter).accept(*tx, *rx, *pp);
            }
            if constexpr (!has_accept){
                return MismatchFlags(ALL);
            }
        }
    };

    /*! \brief Writer of event information
    */
    template <typename C>
    class FilterInfo::Writer : public ObjectInfo::Writer<C> {
    public:
    
        //! Constructor of widget info (this is used by derived classes and this classes other constructor)
        Writer(FilterInfo* pInfo) : ObjectInfo::Writer<C>(pInfo), m_meta(pInfo)
        {
        }
        
        //! Constructor of widget info (this is used by the writer<T>() methods)
        Writer(FilterInfo& pInfo) : Writer(&pInfo)
        {
        }

    private:
        FilterInfo* m_meta;
    };
}
