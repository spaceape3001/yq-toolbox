////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/art/forward.hpp>
#include <yq/core/AllLocal.hpp>
#include <yq/core/Object.hpp>
#include <yq/typedef/xml.hpp>

namespace yq::art {
    class Abstract;
    
    class AbstractMeta : public ObjectMeta {
    public:
        template <typename> class Writer;
        
        AbstractMeta(std::string_view zName, ObjectMeta& base, const std::source_location& sl=std::source_location::current());
        
        uint8_t primary_dimension() const { return m_dimension.primary; }
        bool    support_dimension(uint8_t) const;

    private:
        class Handler;    
        template <typename A, typename T> class CCHandler;
        template <typename A, typename T> class NNHandler;
        template <typename A, typename T> class CNHandler;
        template <typename A, typename T> class NCHandler;
        template <typename A, typename T> class SCHandler;
        template <typename A, typename T> class SNHandler;

        friend class Abstract;
        Map<Meta::id_t, const Handler*> m_handlers;
        const Handler* handler(const Meta&) const;

        struct {
            uint8_t primary = 0;
            uint8_t support = 0;
        } m_dimension;

    };
    
    class Abstract : public Object {
        YQ_OBJECT_META(AbstractMeta)
        YQ_OBJECT_DECLARE(Abstract, Object)
    public:
        
        static void init_meta();
        
        //! Calls a handle
        template <typename D>
        void    handle(D&);
        
        //! Calls a handle 
        template <typename D>
        void    handle(D&) const;

        //! Calls a handle 
        template <typename D>
        void    handle(const D&);
        
        //! Calls a handle 
        template <typename D>
        void    handle(const D&) const;
        
        template <typename A, typename D>
        static void    handle(D&);

        template <typename A, typename D>
        static void    handle(const D&);

        //! Continues current handle call to a base object
        static void    handle(base_k);

        //! User defined key (*should* be unique...however, it's user defined thus YMMV)
        const   std::string& key() const { return m_key; }
        void    set_key(const std::string&);

    protected:
        Abstract();
        ~Abstract();
        
        /*
            Note, by convention... tags starting with a capital letter are treated as 
            children; other things can start with lower case.
        */
        
        virtual void    save_to(XmlNode&) const;
        
        //! Return false if there's issues (note, this won't abort the load, but it'll complain to the user)
        virtual bool    load_from(const XmlNode&);
        
        
    private:
        enum {
            GoBase          = 1,
            NullAbstract    = 2,
            ConstAbstract   = 4,
            ConstData       = 8,
        };

        static void    handle(const Abstract*, const AbstractMeta*, const Meta*, const void*, unsigned opts=0);

        //! These are *USER* defined attributes... (ie... we host, nothing more)
        StringAnyMap        m_attributes;
        std::string         m_key;
    };

    template <typename D>
    void    Abstract::handle(D&data)
    {
        handle(this, &metaInfo(), &meta<D>(), &data);
    }
    
    template <typename D>
    void    Abstract::handle(D& data) const
    {
        handle(this, &metaInfo(), &meta<D>(), &data, ConstAbstract);
    }

    template <typename D>
    void    Abstract::handle(const D&data)
    {
        handle(this, &metaInfo(), &meta<D>(), &data, ConstData);
    }
    
    template <typename D>
    void    Abstract::handle(const D&data) const
    {
        handle(this, &metaInfo(), &meta<D>(), &data, ConstData|ConstAbstract);
    }

}

