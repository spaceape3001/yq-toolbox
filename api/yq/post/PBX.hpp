////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Object.hpp>
#include <yq/post/Dispatcher.hpp>
#include <yq/post/Post.hpp>

namespace yq::post {
    struct PBXDispatch;
    class PBX;
    
    template <typename C>
    concept SomePBX = std::derived_from<C, PBX>;
    
    class PBXInfo : public ObjectInfo {
    public:
        template <typename> class Writer;
        
        PBXInfo(std::string_view zName, const ObjectInfo& base, const std::source_location& sl=std::source_location::current());

    private:
        friend class PBX;
        std::vector<const PBXDispatch*>     m_dispatches;
    };
    
    /*! \brief Object with slots
    
        
    */
    class PBX : public Object, public Dispatcher {
        YQ_OBJECT_INFO(PBXInfo);
        YQ_OBJECT_DECLARE(PBX, Object)
    public:
    
        struct Param : public Dispatcher::Param {
            
        };
        
    protected:
    
        PBX(const Param&, std::initializer_list<R> classFlags={});
        ~PBX();
        
        //! Handles unclaimed posts (so if there's a registered reciever that handles the post, that takes precedence)
        virtual void    handle(const PostCPtr&) {}
        virtual void    receive(const PostCPtr&) override;  // If you override this, you *MUST* call the PBX

        //! Can only register *BEFORE* first post is received
        template <SomePost P, SomePBX C>
        void        reg_receive(void (C::*)(const P&), const TriggerCPtr& trigger={});

        //! Can only register *BEFORE* first post is received
        template <SomePost P, SomePBX C>
        void        reg_receive(bool (C::*)(const P&), const TriggerCPtr& trigger={});

        //! Can only register *BEFORE* first post is received
        template <SomePost P, SomePBX C>
        void        reg_receive(void (C::*)(const Ref<const P>&), const TriggerCPtr& trigger={});

        //! Can only register *BEFORE* first post is received
        template <SomePost P, SomePBX C>
        void        reg_receive(bool (C::*)(const Ref<const P>&), const TriggerCPtr& trigger={});
        
    private:
        using dispatch_span_t = std::span<const PBXDispatch*>;
    
        //std::unordered_map<const PostInfo*, dispatch_span_t>    m_lookup;
        //std::vector<const PBXDispatch*>                         m_dispatch;   // will transition to these
        std::unordered_map<const PostInfo*, const PBXDispatch*>     m_dispatch;
        std::vector<const PBXDispatch*>                             m_custom;
        bool                                                        m_built = false;
        
        struct Rank {
            unsigned            depth;
            const PostInfo*     info    = nullptr;
            const PBXDispatch*  fn      = nullptr;
        };
        
        using rank_vector_t = std::vector<Rank>;
        
        void    _add(rank_vector_t&, const PBXDispatch*, unsigned depth);
        void    _add(rank_vector_t&, const PBXInfo&, unsigned depth);
        void    _build();
    };
    
}
