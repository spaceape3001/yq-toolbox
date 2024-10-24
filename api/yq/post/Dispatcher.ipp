////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Dispatcher.hpp"
#include <yq/container/Stack.hpp>
#include <yq/container/vector_utils.hpp>
#include <yq/core/Object.hpp>
#include <stack>

namespace yq::post {

    struct Dispatcher::Common {
        std::vector<SnoopFN>        snoops;
        std::vector<FilterFN>       filters;
        std::vector<Dispatcher*>    sockets;
    };
    
    Dispatcher::Common& Dispatcher::common()
    {
        static Common s_ret;
        return s_ret;
    }

    ////////////////////////////////////////////////////////////////////////////

    //  Used to keep track of messages en-route to stop circular dependencies
    struct Dispatcher::Postage {
        Post*                           msg     = nullptr;
        std::set<const Dispatcher*>     senders;
        std::set<const Dispatcher*>     recipients;
        
        Postage() {}
        Postage(Post* m, const Dispatcher* b) : msg(m)
        {
            senders.insert(b);
        }
        
        bool    first(sender_k, const Dispatcher* b)
        {
            return senders.insert(b).second;
        }
        
        bool    first(receiver_k, const Dispatcher* b)
        {
            return recipients.insert(b).second;
        }
    };

    ////////////////////////////////////////////////////////////////////////////

    struct Dispatcher::Thread {
        Stack<Postage>              postage;
        std::vector<Dispatcher*>    sockets;
        
        void    capture(Dispatcher* mbx)
        {
            if(!mbx)
                return ;
            sockets.push_back(mbx);
        }
        
        void    uncapture(Dispatcher* mbx)
        {
            if(!mbx)
                return ;
            
            std::erase(sockets, mbx);
            auto itr = std::find(sockets.rbegin(), sockets.rend(), mbx);
            if(itr == sockets.rend())
                return ;
            sockets.erase(itr.base());
        }
    };
    
    Dispatcher::Thread&    Dispatcher::thread()
    {
        static thread_local Thread s_ret;
        return s_ret;
    }

    ////////////////////////////////////////////////////////////////////////////
    
    Dispatcher::Capture::Capture(Dispatcher*mbx) : m_box(mbx)
    {
        thread().capture(mbx);
    }

    Dispatcher::Capture::Capture()
    {
    }
    
    Dispatcher::Capture::~Capture()
    {
        thread().uncapture(m_box);
    }

    Dispatcher::Capture::Capture(Capture&&mv) : m_box(mv.m_box)
    {
        mv.m_box    = nullptr;
    }
    
    Dispatcher::Capture& Dispatcher::Capture::operator=(Capture&& mv)
    {
        if(this != &mv){
            thread().uncapture(m_box);
            m_box       = mv.m_box;
            mv.m_box    = nullptr;
        }
        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////

    Dispatcher::Binding::Binding(Dispatcher& tx, Dispatcher& rx) : m_sender(tx), m_recipient(rx)
    {
    }

    Dispatcher::Binding::~Binding()
    {
        m_filters   = {};
        m_snoops    = {};
    }

    Dispatcher::Binding&    Dispatcher::Binding::operator<<(SnoopFN&&fn)
    {
        m_snoops.push_back(std::move(fn));
        return *this;
    }
    
    Dispatcher::Binding&    Dispatcher::Binding::operator<<(FilterFN&&fn)
    {
        m_filters.push_back(std::move(fn));
        return *this;
    }
    
    bool    Dispatcher::Binding::accept(const Post&p) const
    {
        static Common& g    = common();
        for(const FilterFN& f : m_filters){
            if(!f(m_sender, m_recipient, p))
                return false;
        }
        for(const FilterFN& f : m_sender.m_tx.filters){
            if(!f(m_sender, m_recipient, p))
                return false;
        }
        for(const FilterFN& f : m_recipient.m_rx.filters){
            if(!f(m_sender, m_recipient, p))
                return false;
        }
        for(const FilterFN& f : m_sender.m_filters){
            if(!f(m_sender, m_recipient, p))
                return false;
        }
        for(const FilterFN& f : m_recipient.m_filters){
            if(!f(m_sender, m_recipient, p))
                return false;
        }
        for(const FilterFN& f : g.filters){
            if(!f(m_sender, m_recipient, p))
                return false;
        }
        return true;
    }
    
    Dispatcher::Binding&    Dispatcher::Binding::name(std::string_view k)
    {
        m_name  = std::string(k);
        return *this;
    }

    void    Dispatcher::Binding::snoop(const Post&p) const
    {
        static Common& g    = common();
        for(const SnoopFN& f : m_snoops){
            f(m_sender, m_recipient, p);
        }
        for(const SnoopFN& f : m_sender.m_tx.snoops){
            f(m_sender, m_recipient, p);
        }
        for(const SnoopFN& f : m_recipient.m_rx.snoops){
            f(m_sender, m_recipient, p);
        }
        for(const SnoopFN& f : m_sender.m_snoops){
            f(m_sender, m_recipient, p);
        }
        for(const SnoopFN& f : m_recipient.m_snoops){
            f(m_sender, m_recipient, p);
        }
        for(const SnoopFN& f : g.snoops){
            f(m_sender, m_recipient, p);
        }
    }
    

    ////////////////////////////////////////////////////////////////////////////

    //! Connects two dispatchers
    Dispatcher::Binding&    Dispatcher::connect(Dispatcher& tx, Dispatcher& rx)
    {
        Binding*    b   = new Binding(tx, rx);
        rx.m_tx.connections.push_back(b);
        tx.m_rx.connections.push_back(b);
        return *b;
    }


    size_t  Dispatcher::disconnect(Dispatcher& from, Dispatcher& to)
    {
        std::set<Binding*>  removes;
        eraser_if(from.m_tx.connections, [&](Binding *b) -> bool {
            return &b->recipient() == &to;
        }, [&](Binding *b) {
            removes.insert(b);
        });
        
        std::erase_if(to.m_rx.connections, [&](Binding*b) -> bool {
            return removes.contains(b);
        });
        
        size_t  ret = removes.size();
        for(Binding* b : removes)
            delete b;
        return ret;
    }
    
    size_t  Dispatcher::disconnect(all_t, Dispatcher& to)
    {
        //  Doing it this way in prep for multithreading safety
        std::vector<Binding*>   removed;
        std::swap(removed, to.m_rx.connections);
        for(Binding *b : removed){
            std::erase(b->m_sender.m_tx.connections, b);
        } 
        for(Binding* b : removed){
            delete b;
        }
        return removed.size();
    }
    
    size_t  Dispatcher::disconnect(Dispatcher& from, all_t)
    {
        //  Doing it this way in prep for multithreading safety
        std::vector<Binding*>   removed;
        std::swap(removed, from.m_tx.connections);
        for(Binding* b : removed){
            std::erase(b->m_recipient.m_rx.connections, b);
        }
        for(Binding* b : removed){
            delete b;
        }
        return removed.size();
    }
        
    size_t  Dispatcher::disconnect(Dispatcher& from, Dispatcher& to, std::string_view k)
    {
        std::set<Binding*>  removed;
        eraser_if(from.m_tx.connections, [&](Binding *b) -> bool {
            return (&b->recipient() == &to) && (b->name() == k);
        }, [&](Binding *b) {
            removed.insert(b);
        });
        
        std::erase_if(to.m_rx.connections, [&](Binding*b) -> bool {
            return removed.contains(b);
        });
        
        for(Binding* b : removed)
            delete b;
        return removed.size();
    }
    
    size_t  Dispatcher::disconnect(all_t, Dispatcher& to, std::string_view k)
    {
        std::vector<Binding*> removed;
        eraser_if(to.m_rx.connections, [&](Binding *b) -> bool {
            return b->name() == k;
        }, [&](Binding *b) {
            std::erase(b->m_sender.m_tx.connections, b);
            removed.push_back(b);
        });
        for(Binding* b : removed)
            delete b;
        return removed.size();
    }
    
    size_t  Dispatcher::disconnect(Dispatcher& from, all_t, std::string_view k)
    {
        std::vector<Binding*> removed;
        eraser_if(from.m_tx.connections, [&](Binding *b) -> bool {
            return b->name() == k;
        }, [&](Binding *b) {
            std::erase(b->m_recipient.m_rx.connections, b);
            removed.push_back(b);
        });
        for(Binding* b : removed)
            delete b;
        return removed.size();
    }
    

    ////////////////////////////////////////////////////////////////////////////

    Dispatcher::Dispatcher()
    {
    }
    
    Dispatcher::~Dispatcher()
    {
        disconnect(ALL);
        if(m_flags[F::GlobalCapture]){
            std::erase(common().sockets, this);
        }
    }

    bool    Dispatcher::_accept(Dispatcher& rx, const Post&p)
    {
        static Common& g    = common();
        for(const FilterFN& f : m_tx.filters){
            if(!f(*this, rx, p))
                return false;
        }
        for(const FilterFN& f : rx.m_rx.filters){
            if(!f(*this, rx, p))
                return false;
        }
        for(const FilterFN& f : m_filters){
            if(!f(*this, rx, p))
                return false;
        }
        for(const FilterFN& f : rx.m_filters){
            if(!f(*this, rx, p))
                return false;
        }
        for(const FilterFN& f : g.filters){
            if(!f(*this, rx, p))
                return false;
        }
        return true;
    }

    void    Dispatcher::_dispatch(PostPtr msg)
    {
        static Common& g = common();
        
        Thread&  t = thread();
        Postage& p = t.postage.top();
        
        if(!p.first(TX, this))  // already sent from this dispatcher
            return ;

        for(Dispatcher* b : g.sockets){
            if(!p.first(RX, b))
                continue;
            if(!_accept(*b, *msg))
                continue;
            _snoop(*b, *msg);
            b -> _receive(msg);
        }
            
        for(Dispatcher* b : t.sockets){
            if(!p.first(RX, b))
                continue;
            if(!_accept(*b, *msg))
                continue;
            _snoop(*b, *msg);
            b -> _receive(msg);
        }
        
        
        for(Binding* c : m_tx.connections){
            if(!p.first(RX, &c->m_recipient))
                continue;
            if(!c->accept(*msg))
                continue;
            c -> snoop(*msg);
            c -> m_recipient._receive(msg);
        }
        
        ++(m_tx.usage);
    }

    void    Dispatcher::_receive(PostPtr msg)
    {
        receive(msg);
        ++(m_rx.usage);
    }
    
    void    Dispatcher::_snoop(Dispatcher& rx, const Post& p)
    {
        static Common& g    = common();
        for(const SnoopFN& f : m_tx.snoops){
            f(*this, rx, p);
        }
        for(const SnoopFN& f : rx.m_rx.snoops){
            f(*this, rx, p);
        }
        for(const SnoopFN& f : m_snoops){
            f(*this, rx, p);
        }
        for(const SnoopFN& f : rx.m_snoops){
            f(*this, rx, p);
        }
        for(const SnoopFN& f : g.snoops){
            f(*this, rx, p);
        }
    }

    void    Dispatcher::capture(global_t)
    {
        common().sockets.push_back(this);
        m_flags |= F::GlobalCapture;
    }

    Dispatcher::Capture     Dispatcher::capture(thread_t)
    {
        return Capture(this);
    }

    std::string_view    Dispatcher::description() const
    {
        if(!m_description.empty())
            return m_description;
            
        if(const Object* obj = dynamic_cast<const Object*>(this)){
            return obj -> metaInfo().description();
        }
        
        return "Generic Post Dispatcher";
    }

    void        Dispatcher::description(std::string_view k)
    {
        m_description = std::string(k);
    }

    void        Dispatcher::dispatch(PostPtr msg, Post::flag_initlist_t auxFlags)
    {
        if(!msg.valid())
            return ;
            
        auto& t = thread();
        bool    pushed  = false;

        // Claim ownership if unassigned
        if(!msg->m_originator){
            ++m_balance;
            for(Post::flag_t f : auxFlags)
                msg->m_flags.set(f);
            msg->m_originator   = this;
        }
        
        // Check for circular sending loops
        if(t.postage.empty() || (t.postage.top().msg != msg.ptr())){
            t.postage << Postage(msg.ptr(), this);
            pushed  = true;
        }

        _dispatch(msg);
        
        if(pushed){
            t.postage.pop();
        }
    }

    Dispatcher::Binding&     Dispatcher::connect(sender_k, Dispatcher& sender)
    {
        return connect(sender, *this);
    }

    Dispatcher::Binding&     Dispatcher::connect(receiver_k, Dispatcher& recipient)
    {
        return connect(*this, recipient);
    }

    size_t  Dispatcher::connections(count_t) const
    {
        return m_tx.connections.size() + m_rx.connections.size();
    }
    
    size_t  Dispatcher::connections(count_t, sender_k) const
    {
        return m_tx.connections.size();
    }
    
    size_t  Dispatcher::connections(count_t, receiver_k) const
    {
        return m_rx.connections.size();
    }

    size_t  Dispatcher::disconnect(Dispatcher& other)
    {
        return disconnect(other, *this) + disconnect(*this, other);
    }

    size_t  Dispatcher::disconnect(Dispatcher& other, std::string_view k)
    {
        return disconnect(other, *this, k) + disconnect(*this, other, k);
    }

    size_t  Dispatcher::disconnect(all_t)
    {
        return disconnect(ALL, *this) + disconnect(*this, ALL);
    }

    size_t  Dispatcher::disconnect(all_t, std::string_view k)
    {
        return disconnect(ALL, *this, k) + disconnect(*this, ALL, k);
    }

    size_t  Dispatcher::disconnect(receiver_k, Dispatcher& recipient)
    {
        return disconnect(*this, recipient);
    }
    
    size_t  Dispatcher::disconnect(receiver_k, Dispatcher& recipient, std::string_view k)
    {
        return disconnect(*this, recipient, k);
    }

    size_t  Dispatcher::disconnect(receiver_k, all_t)
    {
        return disconnect(*this, ALL);
    }
    
    size_t  Dispatcher::disconnect(receiver_k, all_t, std::string_view k)
    {
        return disconnect(*this, ALL, k);
    }

    size_t  Dispatcher::disconnect(sender_k, Dispatcher& sender)
    {
        return disconnect(sender, *this);
    }

    size_t  Dispatcher::disconnect(sender_k, Dispatcher& sender, std::string_view k)
    {
        return disconnect(sender, *this, k);
    }

    size_t  Dispatcher::disconnect(sender_k, all_t)
    {
        return disconnect(ALL, *this);
    }

    size_t  Dispatcher::disconnect(sender_k, all_t, std::string_view k)
    {
        return disconnect(ALL, *this, k);
    }
    
#if 0
        //! Installs a global snoop (good for event logging)
        //! This is *NOT* thread-safe call, do it at initialization time.  (ie create & set before use)
        static void install(global_t, SnoopFN&&);
        
        //! Installs a global filter
        //! This is *NOT* thread-safe call, do it at initialization time.  (ie create & set before use)
        static void install(global_t, FilterFN&&);
        
        void install(SnoopFN&&);
        void install(sender_k, SnoopFN&&);
        void install(receiver_k, SnoopFN&&);
        void install(FilterFN&&);
        void install(sender_k, FilterFN&&);
        void install(receiver_k, FilterFN&&);
#endif

    std::string_view    Dispatcher::name() const
    {
        if(!m_name.empty())
            return m_name;
            
        if(const Object* obj = dynamic_cast<const Object*>(this)){
            return obj -> metaInfo().name();
        }
        
        return "post::Dispatcher";
    }

    void        Dispatcher::name(std::string_view k)
    {
        m_name = std::string(k);
    }
    
}
