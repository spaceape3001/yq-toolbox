////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#error "Obsolete, do not include"

/*
    This (the post library) is being removed SOON, however, 
    it's kept around as reference
*/


#include <yq/core/Object.hpp>
#include <yq/core/Required.hpp>
#include <yq/post/Dispatcher.hpp>
#include <yq/post/Post.hpp>

namespace yq::post {
    struct PBXDispatch;
    class PBX;
    
    class PBXInfo : public ObjectInfo {
    public:
        template <typename> class Writer;
        
        PBXInfo(std::string_view zName, ObjectInfo& base, const std::source_location& sl=std::source_location::current());

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
        
        virtual void    receive(const PostCPtr&) override;  // If you override this, you *MUST* call the PBX
        
        static void init_meta();

    protected:
    
        PBX(const Param& p={}, std::initializer_list<R> classFlags={});
        ~PBX();
        
        //! Handles unclaimed posts (so if there's a registered reciever that handles the post, that takes precedence)
        virtual void    handle(const PostCPtr&) {}

        //! Can only register *BEFORE* first post is received
        template <SomePost P, SomePBX C>
        void        reg_receive(void (C::*)(const P&), const TriggerCPtr& trigger={}, MismatchPolicy mp=MismatchPolicy::Reject);

        //! Can only register *BEFORE* first post is received
        template <SomePost P, SomePBX C>
        void        reg_receive(bool (C::*)(const P&), const TriggerCPtr& trigger={}, MismatchPolicy mp=MismatchPolicy::Reject);

        //! Can only register *BEFORE* first post is received
        template <SomePost P, SomePBX C>
        void        reg_receive(void (C::*)(const Ref<const P>&), const TriggerCPtr& trigger={}, MismatchPolicy mp=MismatchPolicy::Reject);

        //! Can only register *BEFORE* first post is received
        template <SomePost P, SomePBX C>
        void        reg_receive(bool (C::*)(const Ref<const P>&), const TriggerCPtr& trigger={}, MismatchPolicy mp=MismatchPolicy::Reject);
        
        //! Can only register *BEFORE* first post is received
        template <SomePBX C>
        void        reg_receive(void (C::*)(), const TriggerCPtr& trigger={}, MismatchPolicy mp=MismatchPolicy::Reject);

        template <SomePBX C>
        void        reg_receive(bool (C::*)(), const TriggerCPtr& trigger={}, MismatchPolicy mp=MismatchPolicy::Reject);

    private:
        using dispatch_span_t = std::span<const PBXDispatch*>;
    
        std::unordered_map<const PostInfo*, dispatch_span_t>        m_lookup;
        std::vector<const PBXDispatch*>                             m_dispatch;   // will transition to these
        std::vector<const PBXDispatch*>                             m_custom;
        bool                                                        m_built = false;
        
        struct Entry;
        
        using entry_vector_t = std::vector<Entry>;
        
        void    _add(entry_vector_t&, const PBXDispatch*, unsigned depth);
        void    _add(entry_vector_t&, const PBXInfo&, unsigned depth);
        void    _build();
        
        bool    _execute(const PBXDispatch&, const PostCPtr&);
    };
    
}
