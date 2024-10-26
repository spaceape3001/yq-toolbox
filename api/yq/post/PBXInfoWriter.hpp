////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/ObjectInfoWriter.hpp>
#include <yq/post/PBX.hpp>
#include <yq/post/Trigger.hpp>

namespace yq::post {

    class PBXDispatch {
    public:
        virtual bool            handle(PBX *, const PostCPtr&) const = 0;
        virtual const PostInfo& post_info() const = 0;
        virtual const PBXInfo&  pbx_info() const = 0;
    };
    
    template <SomePBX C, SomePost P>
    class PBXDispatch_Void : public PBXDispatch {
    public:
        typedef void (C::*FN)();
        FN              m_fn;
        TriggerCPtr     m_trigger;
        
        PBXDispatch_Void(FN fn, const TriggerCPtr& trigger) : m_fn(fn), m_trigger(trigger)
        {
        }
        
        bool  handle(PBX *pbx, const PostCPtr& pp) const override
        {
            if(m_trigger && !m_trigger->accept(*pp))
                return false;
            C*  c   = static_cast<C*>(pbx);
            (c->*m_fn)();
            return true;
        }
        
        const PBXInfo& pbx_info() const override
        {
            return meta<C>();
        }
        
        const PostInfo&  post_info() const override 
        { 
            return meta<P>(); 
        }
    };

    template <SomePBX C, SomePost P>
    class PBXDispatch_Bool : public PBXDispatch {
    public:
        typedef bool (C::*FN)();
        FN              m_fn;
        TriggerCPtr     m_trigger;
        
        PBXDispatch_Bool(FN fn, const TriggerCPtr& trigger) : m_fn(fn), m_trigger(trigger)
        {
        }
        
        bool  handle(PBX *pbx, const PostCPtr& pp) const override
        {
            if(m_trigger && !m_trigger->accept(*pp))
                return false;
            C*  c   = static_cast<C*>(pbx);
            return (c->*m_fn)(static_cast<const P&>(pp));
        }
        
        const PBXInfo& pbx_info() const override
        {
            return meta<C>();
        }

        const PostInfo& post_info() const override 
        { 
            return meta<P>(); 
        }
    };

    template <SomePBX C, SomePost P>
    class PBXDispatch_VoidCRef : public PBXDispatch {
    public:
        typedef void (C::*FN)(const P&);
        FN              m_fn;
        TriggerCPtr     m_trigger;
        
        PBXDispatch_VoidCRef(FN fn, const TriggerCPtr& trigger) : m_fn(fn), m_trigger(trigger)
        {
        }
        
        bool  handle(PBX *pbx, const PostCPtr& pp) const override
        {
            if(m_trigger && !m_trigger->accept(*pp))
                return false;
            C*  c   = static_cast<C*>(pbx);
            (c->*m_fn)(static_cast<const P&>(pp));
            return true;
        }
        
        const PBXInfo& pbx_info() const override
        {
            return meta<C>();
        }
        
        const PostInfo&  post_info() const override 
        { 
            return meta<P>(); 
        }
    };

    template <SomePBX C, SomePost P>
    class PBXDispatch_BoolCRef : public PBXDispatch {
    public:
        typedef bool (C::*FN)(const P&);
        FN              m_fn;
        TriggerCPtr     m_trigger;
        
        PBXDispatch_BoolCRef(FN fn, const TriggerCPtr& trigger) : m_fn(fn), m_trigger(trigger)
        {
        }
        
        bool  handle(PBX *pbx, const PostCPtr& pp) const override
        {
            if(m_trigger && !m_trigger->accept(*pp))
                return false;
            C*  c   = static_cast<C*>(pbx);
            return (c->*m_fn)(static_cast<const P&>(pp));
        }
        
        const PBXInfo& pbx_info() const override
        {
            return meta<C>();
        }

        const PostInfo& post_info() const override 
        { 
            return meta<P>(); 
        }
    };
    
    template <SomePBX C, SomePost P>
    class PBXDispatch_VoidCPtr : public PBXDispatch {
    public:
        typedef void (C::*FN)(const Ref<const P>&);
        FN              m_fn;
        TriggerCPtr     m_trigger;
        
        PBXDispatch_VoidCPtr(FN fn, const TriggerCPtr& trigger) : m_fn(fn)
        {
        }
        
        bool  handle(PBX *pbx, const PostCPtr& pp) const override
        {
            if(m_trigger && !m_trigger->accept(*pp))
                return false;
            C* c   = static_cast<C*>(pbx);
            Ref<const P>    ppp(static_cast<const P*>(pp.ptr()));
            (c->*m_fn)(ppp);
            return true;
        }

        const PBXInfo& pbx_info() const override
        {
            return meta<C>();
        }
        
        const PostInfo& post_info() const override 
        { 
            return meta<P>(); 
        }
    };

    template <SomePBX C, SomePost P>
    class PBXDispatch_BoolCPtr : public PBXDispatch {
    public:
        typedef bool (C::*FN)(const Ref<const P>&);
        FN              m_fn;
        TriggerCPtr     m_trigger;
        
        PBXDispatch_BoolCPtr(FN fn, const TriggerCPtr& trigger) : m_fn(fn)
        {
        }
        
        bool            handle(PBX *pbx, const PostCPtr& pp) const override
        {
            if(m_trigger && !m_trigger->accept(*pp))
                return false;
            C* c   = static_cast<C*>(pbx);
            Ref<const P>    ppp(static_cast<const P*>(pp.ptr()));
            return (c->*m_fn)(ppp);
        }

        const PBXInfo& pbx_info() const override
        {
            return meta<C>();
        }
        
        const PostInfo& post_info() const override 
        { 
            return meta<P>(); 
        }
    };


    /*! \brief Writer of event information
    */
    template <typename C>
    class PBXInfo::Writer : public ObjectInfo::Writer<C> {
    public:
    
        //! Constructor of widget info (this is used by derived classes and this classes other constructor)
        Writer(PBXInfo* pInfo) : ObjectInfo::Writer<C>(pInfo), m_meta(pInfo)
        {
        }
        
        //! Constructor of widget info (this is used by the writer<T>() methods)
        Writer(PBXInfo& pInfo) : Writer(&pInfo)
        {
        }
        
        template <SomePost P, SomePBX C2=C>
        void    receive(void (C2::*fn)(const P&), const TriggerCPtr& trigger={})
        {
            static_assert(std::derived_from<C,C2>, "Incompatible PBX types, need inheritance");
            if(m_meta && Meta::thread_safe_write()){
                m_meta -> m_dispatches.push_back(new PBXDispatch_VoidCRef<C2,P>(fn, trigger));
            }
        }

        template <SomePost P, SomePBX C2=C>
        void    receive(bool (C2::*fn)(const P&), const TriggerCPtr& trigger={})
        {
            static_assert(std::derived_from<C,C2>, "Incompatible PBX types, need inheritance");
            if(m_meta && Meta::thread_safe_write()){
                m_meta -> m_dispatches.push_back(new PBXDispatch_BoolCRef<C2,P>(fn, trigger));
            }
        }

        template <SomePost P, SomePBX C2=C>
        void    receive(void (C2::*fn)(const Ref<const P>&), const TriggerCPtr& trigger={})
        {
            static_assert(std::derived_from<C,C2>, "Incompatible PBX types, need inheritance");
            if(m_meta && Meta::thread_safe_write()){
                m_meta -> m_dispatches.push_back(new PBXDispatch_VoidCPtr<C2,P>(fn, trigger));
            }
        }

        template <SomePost P, SomePBX C2=C>
        void    receive(bool (C2::*fn)(const Ref<const P>&), const TriggerCPtr& trigger={})
        {
            static_assert(std::derived_from<C,C2>, "Incompatible PBX types, need inheritance");
            if(m_meta && Meta::thread_safe_write()){
                m_meta -> m_dispatches.push_back(new PBXDispatch_BoolCPtr<C2,P>(fn, trigger));
            }
        }
        
        template <SomePost P, SomePBX C2=C>
        void    receive(void (C2::*fn)(), const TriggerCPtr& trigger)
        {
            static_assert(std::derived_from<C,C2>, "Incompatible PBX types, need inheritance");
            if(m_meta && Meta::thread_safe_write()){
                m_meta -> m_dispatches.push_back(new PBXDispatch_Void<C2,P>(fn, trigger));
            }
        }

        template <SomePost P, SomePBX C2=C>
        void    receive(bool (C2::*fn)(), const TriggerCPtr& trigger)
        {
            static_assert(std::derived_from<C,C2>, "Incompatible PBX types, need inheritance");
            if(m_meta && Meta::thread_safe_write()){
                m_meta -> m_dispatches.push_back(new PBXDispatch_Bool<C2,P>(fn, trigger));
            }
        }

    private:
        PBXInfo* m_meta;
    };

    template <SomePost P, SomePBX C>
    void        PBX::reg_receive(void (C::*fn)(const P&), const TriggerCPtr& trigger)
    {
        m_custom.push_back(new PBXDispatch_VoidCRef<C,P>(fn, trigger));
    }

    template <SomePost P, SomePBX C>
    void        PBX::reg_receive(bool (C::*fn)(const P&), const TriggerCPtr& trigger)
    {
        m_custom.push_back(new PBXDispatch_BoolCRef<C,P>(fn, trigger));
    }

    template <SomePost P, SomePBX C>
    void        PBX::reg_receive(void (C::*fn)(const Ref<const P>&), const TriggerCPtr& trigger)
    {
        m_custom.push_back(new PBXDispatch_VoidCPtr<C,P>(fn, trigger));
    }

    template <SomePost P, SomePBX C>
    void        PBX::reg_receive(bool (C::*fn)(const Ref<const P>&), const TriggerCPtr& trigger)
    {
        m_custom.push_back(new PBXDispatch_BoolCPtr<C,P>(fn, trigger));
    }
}
