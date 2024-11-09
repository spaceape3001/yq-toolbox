////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/ObjectInfoWriter.hpp>
#include <yq/post/PBX.hpp>
#include <yq/post/Trigger.hpp>
#include <yq/core/Required.hpp>


namespace yq::post {

    class PBXDispatch {
    public:
        
        class Writer;
    
        //! Post it takes (null if post's ignored)
        const PostInfo*     post_info() const { return m_post; }
        
        //! PBX it's declared on
        const PBXInfo*      pbx_info() const { return m_pbx; }
        
        //! And the trigger
        const TriggerCPtr&  trigger() const { return m_trigger; }
        
        std::string_view    name() const { return m_name; }
        
        virtual const char* debug_string() const = 0;
        
    protected:
        friend class PBX;
        PBXDispatch(const TriggerCPtr& trig, MismatchPolicy mp) : m_trigger(trig), m_mismatch(mp) {}
        virtual ~PBXDispatch(){}
        
        virtual bool        dispatch(PBX&, const PostCPtr&) const = 0;
    
        const PostInfo*     m_post          = nullptr;
        const PBXInfo*      m_pbx           = nullptr;
        std::string_view    m_name;
    
        TriggerCPtr         m_trigger       = {};

        //! How to respond to a mismatch in the trigger/presented post
        MismatchPolicy      m_mismatch      = MismatchPolicy::Reject;
    };
    
    
    template <SomePBX C>
    class PBXDispatch_Void : public PBXDispatch {
    public:
        typedef void (C::*FN)();
        FN              m_fn;
        
        PBXDispatch_Void(FN fn, const TriggerCPtr& trigger, MismatchPolicy mp) : PBXDispatch(trigger, mp), m_fn(fn)
        {
            m_pbx   = &meta<C>();
        }
        
        bool  dispatch(PBX& pbx, const PostCPtr& pp) const override
        {
            C&  c   = static_cast<C&>(pbx);
            (c.*m_fn)();
            return true;
        }
        
        const char* debug_string() const override
        {
            return "void(C::*)()";
        }
    };

    template <SomePBX C>
    class PBXDispatch_Bool : public PBXDispatch {
    public:
        typedef bool (C::*FN)();
        FN              m_fn;
        
        PBXDispatch_Bool(FN fn, const TriggerCPtr& trigger, MismatchPolicy mp) : PBXDispatch(trigger, mp), m_fn(fn)
        {
            m_pbx   = &meta<C>();
        }
        
        bool  dispatch(PBX &pbx, const PostCPtr& pp) const override
        {
            C&  c   = static_cast<C&>(pbx);
            return (c.*m_fn)();
        }

        const char* debug_string() const override
        {
            return "bool(C::*)()";
        }
    };

    template <SomePBX C, SomePost P>
    class PBXDispatch_VoidCRef : public PBXDispatch {
    public:
        typedef void (C::*FN)(const P&);
        FN              m_fn;
        
        PBXDispatch_VoidCRef(FN fn, const TriggerCPtr& trigger, MismatchPolicy mp) : PBXDispatch(trigger, mp), m_fn(fn)
        {
            m_pbx   = &meta<C>();
            m_post  = &meta<P>();
        }
        
        bool  dispatch(PBX &pbx, const PostCPtr& pp) const override
        {
            C&  c   = static_cast<C&>(pbx);
            (c.*m_fn)(static_cast<const P&>(*pp));
            return true;
        }

        const char* debug_string() const override
        {
            return "void(C::*)(const P&)";
        }
    };

    template <SomePBX C, SomePost P>
    class PBXDispatch_BoolCRef : public PBXDispatch {
    public:
        typedef bool (C::*FN)(const P&);
        FN              m_fn;
        
        PBXDispatch_BoolCRef(FN fn, const TriggerCPtr& trigger, MismatchPolicy mp) : PBXDispatch(trigger, mp), m_fn(fn)
        {
            m_pbx   = &meta<C>();
            m_post  = &meta<P>();
        }
        
        bool  dispatch(PBX &pbx, const PostCPtr& pp) const override
        {
            C&  c   = static_cast<C&>(pbx);
            return (c.*m_fn)(static_cast<const P&>(*pp));
        }

        const char* debug_string() const override
        {
            return "bool(C::*)(const P&)";
        }
    };
    
    template <SomePBX C, SomePost P>
    class PBXDispatch_VoidCPtr : public PBXDispatch {
    public:
        typedef void (C::*FN)(const Ref<const P>&);
        FN              m_fn;
        
        PBXDispatch_VoidCPtr(FN fn, const TriggerCPtr& trigger, MismatchPolicy mp) : PBXDispatch(trigger, mp), m_fn(fn)
        {
            m_pbx   = &meta<C>();
            m_post  = &meta<P>();
        }
        
        bool  dispatch(PBX &pbx, const PostCPtr& pp) const override
        {
            C&  c   = static_cast<C&>(pbx);
            Ref<const P>    ppp(static_cast<const P*>(pp.ptr()));
            (c.*m_fn)(ppp);
            return true;
        }

        const char* debug_string() const override
        {
            return "void(C::*)(const Ref<P>&)";
        }
    };

    template <SomePBX C, SomePost P>
    class PBXDispatch_BoolCPtr : public PBXDispatch {
    public:
        typedef bool (C::*FN)(const Ref<const P>&);
        FN              m_fn;
        
        PBXDispatch_BoolCPtr(FN fn, const TriggerCPtr& trigger, MismatchPolicy mp) : PBXDispatch(trigger, mp), m_fn(fn)
        {
        }
        
        bool  dispatch(PBX &pbx, const PostCPtr& pp) const override
        {
            C&  c   = static_cast<C&>(pbx);
            Ref<const P>    ppp(static_cast<const P*>(pp.ptr()));
            return (c.*m_fn)(ppp);
        }

        const char* debug_string() const override
        {
            return "bool(C::*)(const Ref<P>&)";
        }
    };

    class PBXDispatch::Writer {
    public:
        Writer(PBXDispatch* pbx=nullptr) : m_pbx(pbx) {}
        
        Writer& name(std::string_view v) 
        {
            if(m_pbx){
                m_pbx -> m_name = v;
            }
            return *this;
        }
        
    private:
        PBXDispatch*    m_pbx;
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
        PBXDispatch::Writer    receive(void (C2::*fn)(const P&), const TriggerCPtr& trigger={}, MismatchPolicy mp=MismatchPolicy::Reject)
        {
            static_assert(std::derived_from<C,C2>, "Incompatible PBX types, need inheritance");
            if(m_meta && Meta::thread_safe_write()){
                PBXDispatch*    ret = new PBXDispatch_VoidCRef<C2,P>(fn, trigger, mp);
                m_meta -> m_dispatches.push_back(ret);
                return ret;
            }
            return {};
        }

        template <SomePost P, SomePBX C2=C>
        PBXDispatch::Writer    receive(bool (C2::*fn)(const P&), const TriggerCPtr& trigger={}, MismatchPolicy mp=MismatchPolicy::Reject)
        {
            static_assert(std::derived_from<C,C2>, "Incompatible PBX types, need inheritance");
            if(m_meta && Meta::thread_safe_write()){
                PBXDispatch*    ret = new PBXDispatch_BoolCRef<C2,P>(fn, trigger, mp);
                m_meta -> m_dispatches.push_back(ret);
                return ret;
            }
            return {};
        }

        template <SomePost P, SomePBX C2=C>
        PBXDispatch::Writer    receive(void (C2::*fn)(const Ref<const P>&), const TriggerCPtr& trigger={}, MismatchPolicy mp=MismatchPolicy::Reject)
        {
            static_assert(std::derived_from<C,C2>, "Incompatible PBX types, need inheritance");
            if(m_meta && Meta::thread_safe_write()){
                PBXDispatch*    ret = new PBXDispatch_VoidCPtr<C2,P>(fn, trigger, mp);
                m_meta -> m_dispatches.push_back(ret);
                return ret;
            }
            return {};
        }

        template <SomePost P, SomePBX C2=C>
        PBXDispatch::Writer    receive(bool (C2::*fn)(const Ref<const P>&), const TriggerCPtr& trigger={}, MismatchPolicy mp=MismatchPolicy::Reject)
        {
            static_assert(std::derived_from<C,C2>, "Incompatible PBX types, need inheritance");
            if(m_meta && Meta::thread_safe_write()){
                PBXDispatch*    ret = new PBXDispatch_BoolCPtr<C2,P>(fn, trigger, mp);
                m_meta -> m_dispatches.push_back(ret);
                return ret;
            }
            return {};
        }
        
        template <SomePBX C2=C>
        PBXDispatch::Writer    receive(void (C2::*fn)(), const TriggerCPtr& trigger={}, MismatchPolicy mp=MismatchPolicy::Reject)
        {
            static_assert(std::derived_from<C,C2>, "Incompatible PBX types, need inheritance");
            if(m_meta && Meta::thread_safe_write()){
                PBXDispatch*    ret = new PBXDispatch_Void<C2>(fn, trigger, mp);
                m_meta -> m_dispatches.push_back(ret);
                return ret;
            }
            return {};
        }

        template <SomePBX C2=C>
        PBXDispatch::Writer    receive(bool (C2::*fn)(), const TriggerCPtr& trigger={}, MismatchPolicy mp=MismatchPolicy::Reject)
        {
            static_assert(std::derived_from<C,C2>, "Incompatible PBX types, need inheritance");
            if(m_meta && Meta::thread_safe_write()){
                PBXDispatch*    ret = new PBXDispatch_Bool<C2>(fn, trigger, mp);
                m_meta -> m_dispatches.push_back(ret);
                return ret;
            }
            return {};
        }

    private:
        PBXInfo* m_meta;
    };

    template <SomePost P, SomePBX C>
    void        PBX::reg_receive(void (C::*fn)(const P&), const TriggerCPtr& trigger, MismatchPolicy mp)
    {
        m_custom.push_back(new PBXDispatch_VoidCRef<C,P>(fn, trigger, mp));
    }

    template <SomePost P, SomePBX C>
    void        PBX::reg_receive(bool (C::*fn)(const P&), const TriggerCPtr& trigger, MismatchPolicy mp)
    {
        m_custom.push_back(new PBXDispatch_BoolCRef<C,P>(fn, trigger, mp));
    }

    template <SomePost P, SomePBX C>
    void        PBX::reg_receive(void (C::*fn)(const Ref<const P>&), const TriggerCPtr& trigger, MismatchPolicy mp)
    {
        m_custom.push_back(new PBXDispatch_VoidCPtr<C,P>(fn, trigger, mp));
    }

    template <SomePost P, SomePBX C>
    void        PBX::reg_receive(bool (C::*fn)(const Ref<const P>&), const TriggerCPtr& trigger, MismatchPolicy mp)
    {
        m_custom.push_back(new PBXDispatch_BoolCPtr<C,P>(fn, trigger, mp));
    }

    template <SomePBX C>
    void        PBX::reg_receive(void (C::*fn)(), const TriggerCPtr& trigger, MismatchPolicy mp)
    {
        m_custom.push_back(new PBXDispatch_Void<C>(fn, trigger, mp));
    }

    template <SomePBX C>
    void        PBX::reg_receive(bool (C::*fn)(), const TriggerCPtr& trigger, MismatchPolicy mp)
    {
        m_custom.push_back(new PBXDispatch_Bool<C>(fn, trigger, mp));
    }

}
