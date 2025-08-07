////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/art/Abstract.hpp>
#include <yq/meta/ObjectMetaWriter.hpp>
#include <yq/meta/UntypeMeta.hpp>

namespace yq::art {

        // move to object itself.... (once verified to work)
    class AbstractMeta::Handler {
    public:
        virtual bool    abs_const() const = 0;
        virtual bool    data_const() const = 0;

        virtual void    invoke(Abstract*, void*) const = 0;
        
        const bool      m_null;     // true if null
        const bool      m_abs;      // true if const
        const bool      m_data;     // true if const
    
    protected:
        Handler(bool n, bool a, bool d) : m_null(n), m_abs(a), m_data(d) {}
    };
    
    
    template <typename A, typename D> 
    class AbstractMeta::CCHandler : public Handler {
    public:
        typedef void (*FN)(const A&, const D&);
        
        CCHandler(FN fn) : Handler(false, true, true), m_fn(fn)
        {
        }
        
        void    invoke(Abstract* a, void* d) const
        {
            m_fn(*static_cast<A*>(a), *static_cast<D*>(d));
        }
        
    private:
        FN      m_fn;
    };

    template <typename A, typename D> 
    class AbstractMeta::CNHandler : public Handler {
    public:
        typedef void (*FN)(const A&, D&);
        
        CNHandler(FN fn) : Handler(false, true, false), m_fn(fn)
        {
        }
        
        void    invoke(Abstract* a, void* d) const
        {
            m_fn(*static_cast<A*>(a), *static_cast<D*>(d));
        }
        
    private:
        FN      m_fn;
    };

    template <typename A, typename D> 
    class AbstractMeta::NCHandler : public Handler {
    public:
        typedef void (*FN)(A&, const D&);
        
        NCHandler(FN fn) : Handler(false, false, true), m_fn(fn)
        {
        }
        
        void    invoke(Abstract* a, void* d) const
        {
            m_fn(*static_cast<A*>(a), *static_cast<D*>(d));
        }
        
    private:
        FN      m_fn;
    };
    

    template <typename A, typename D> 
    class AbstractMeta::NNHandler : public Handler {
    public:
        typedef void (*FN)(A&, D&);
        
        NNHandler(FN fn) : Handler(false, false, false), m_fn(fn)
        {
        }
        
        void    invoke(Abstract* a, void* d) const
        {
            m_fn(*static_cast<A*>(a), *static_cast<D*>(d));
        }
        
    private:
        FN      m_fn;
    };
    
    template <typename A, typename D> 
    class AbstractMeta::SCHandler : public Handler {
    public:
        typedef void (*FN)(const D&);
        
        SCHandler(FN fn) : Handler(true, false, true), m_fn(fn)
        {
        }
        
        void    invoke(Abstract*, void* d) const
        {
            m_fn(*static_cast<D*>(d));
        }
        
    private:
        FN      m_fn;
    };
    

    template <typename A, typename D> 
    class AbstractMeta::SNHandler : public Handler {
    public:
        typedef void (*FN)(D&);
        
        SNHandler(FN fn) : Handler(true, false, false), m_fn(fn)
        {
        }
        
        void    invoke(Abstract* a, void* d) const
        {
            m_fn(*static_cast<D*>(d));
        }
        
    private:
        FN      m_fn;
    };

    template <typename A>
    class AbstractMeta::Writer : public ObjectMeta::Writer<A> {
    public:
        Writer(AbstractMeta* dInfo) : ObjectMeta::Writer<A>(dInfo), m_meta(dInfo)
        {
        }
        
        Writer(AbstractMeta& dInfo) : Writer(&dInfo)
        {
        }

        template <typename D>
        Writer& handler(void (*fn)(const A&, const D&))
        {
            if(fn && m_meta && Meta::thread_safe_write()){
                m_meta -> m_handlers[meta<D>().id()] = new CCHandler<A,D>(fn);
            }
            return *this;
        }

        template <typename D>
        Writer& handler(void (*fn)(const A&, D&))
        {
            if(fn && m_meta && Meta::thread_safe_write()){
                m_meta -> m_handlers[meta<D>().id()] = new CNHandler<A,D>(fn);
            }
            return *this;
        }

        template <typename D>
        Writer& handler(void (*fn)(A&, const D&))
        {
            if(fn && m_meta && Meta::thread_safe_write()){
                m_meta -> m_handlers[meta<D>().id()] = new NCHandler<A,D>(fn);
            }
            return *this;
        }

        template <typename D>
        Writer& handler(void (*fn)(A&, D&))
        {
            if(fn && m_meta && Meta::thread_safe_write()){
                m_meta -> m_handlers[meta<D>().id()] = new NNHandler<A,D>(fn);
            }
            return *this;
        }
        
        template <typename D>
        Writer& handler(void (*fn)(const D&))
        {
            if(fn && m_meta && Meta::thread_safe_write()){
                m_meta -> m_handlers[meta<D>().id()] = new SCHandler<A,D>(fn);
            }
            return *this;
        }

        template <typename D>
        Writer& handler(void (*fn)(D&))
        {
            if(fn && m_meta && Meta::thread_safe_write()){
                m_meta -> m_handlers[meta<D>().id()] = new SNHandler<A,D>(fn);
            }
            return *this;
        }

        Writer& dimension(uint8_t n, std::initializer_list<uint8_t> others={})
        {
            if(m_meta && Meta::thread_safe_write()){
                if(n<=7){
                    m_dimension.primary = n;
                    m_dimension.support = (uint8_t)(1 << n);
                }
                for(uint8_t o : others){
                    if(n > 7)
                        continue;
                    m_dimension.support |= (uint8_t)(1<<o);
                }
            }
            return *this;
        }
        

    private:
        AbstractMeta*    m_meta;
    };
}

