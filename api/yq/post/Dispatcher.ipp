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
#include <yq/post/Filter.hpp>
#include <yq/post/logging.hpp>
#include <stack>

namespace yq::post {

    struct Dispatcher::Common {
        std::vector<SnoopFN>        snoops;
        std::vector<FilterCPtr>     filters;
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
        const Post*                     msg     = nullptr;
        std::set<const Dispatcher*>     senders;
        std::set<const Dispatcher*>     recipients;
        
        Postage() {}
        Postage(const Post* m) : msg(m)
        {
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
    
    Dispatcher::Binding&    Dispatcher::Binding::operator<<(const FilterCPtr& fn)
    {
        m_filters.push_back(fn);
        return *this;
    }
    
    bool    Dispatcher::Binding::accept(const Post&p) const
    {
        static Common& g    = common();
        for(const FilterCPtr& f : m_filters){
            if(!f->passed(m_sender, m_recipient, p))
                return false;
        }
        for(const FilterCPtr& f : m_sender.m_tx.filters){
            if(!f->passed(m_sender, m_recipient, p))
                return false;
        }
        for(const FilterCPtr& f : m_recipient.m_rx.filters){
            if(!f->passed(m_sender, m_recipient, p))
                return false;
        }
        for(const FilterCPtr& f : m_sender.m_filters){
            if(!f->passed(m_sender, m_recipient, p))
                return false;
        }
        for(const FilterCPtr& f : m_recipient.m_filters){
            if(!f->passed(m_sender, m_recipient, p))
                return false;
        }
        for(const FilterCPtr& f : g.filters){
            if(!f->passed(m_sender, m_recipient, p))
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
        rx.m_rx.connections.push_back(b);
        tx.m_tx.connections.push_back(b);
        
        if(tx.m_logging(Log::Connections) || rx.m_logging(Log::Connections)){
            postInfo << "Dispatcher::connect(" << tx.name() << ">>" << rx.name() << ")";
        }
        
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
    
    void Dispatcher::install(global_t, const FilterCPtr& fn)
    {
        if(fn){
            common().filters.push_back(fn);
        }
    }
        

    ////////////////////////////////////////////////////////////////////////////

    Dispatcher::Dispatcher() : Dispatcher(Param())
    {
    }

    Dispatcher::Dispatcher(const Param& p, std::initializer_list<R> flags) : m_name(p.name), 
        m_description(p.description), m_roles(flags), m_logging(p.logging)
    {
        if(m_roles[R::GlobalCapture])
            common().sockets.push_back(this);
    }
    
    Dispatcher::~Dispatcher()
    {
        disconnect(ALL);
        if(m_roles[R::GlobalCapture]){
            std::erase(common().sockets, this);
        }
    }

    bool    Dispatcher::_accept(Dispatcher& rx, const Post&p)
    {
        static Common& g    = common();
        for(const FilterCPtr& f : m_tx.filters){
            if(!f->passed(*this, rx, p))
                return false;
        }
        for(const FilterCPtr& f : rx.m_rx.filters){
            if(!f->passed(*this, rx, p))
                return false;
        }
        for(const FilterCPtr& f : m_filters){
            if(!f->passed(*this, rx, p))
                return false;
        }
        for(const FilterCPtr& f : rx.m_filters){
            if(!f->passed(*this, rx, p))
                return false;
        }
        for(const FilterCPtr& f : g.filters){
            if(!f->passed(*this, rx, p))
                return false;
        }
        return true;
    }

    void    Dispatcher::_dispatch(const PostCPtr& msg, bool self)
    {
        static Common& g = common();
        
        Thread&  t = thread();
        Postage& p = t.postage.top();
        
        if(!p.first(TX, this))  // already sent from this dispatcher
            return ;
            
        if(self){
            _receive(msg);
        }
            
        uint64_t    cnt = 0;

        for(Dispatcher* b : g.sockets){
            if(!b)
                continue;
            if(!p.first(RX, b))
                continue;
            if(!_accept(*b, *msg))
                continue;
            _snoop(*b, *msg);
            
            b -> _receive(msg);
            ++cnt;
        }
            
        for(Dispatcher* b : t.sockets){
            if(!b)
                continue;
            if(!p.first(RX, b))
                continue;
            if(!_accept(*b, *msg))
                continue;
            _snoop(*b, *msg);
            b -> _receive(msg);
            ++cnt;
        }
        
        
        for(Binding* c : m_tx.connections){
            if(!p.first(RX, &c->m_recipient))
                continue;
            if(!c->accept(*msg))
                continue;
            c -> snoop(*msg);
            c -> m_recipient._receive(msg);
            ++cnt;
        }

        ++(m_tx.usage);

        if(m_logging(Log::Dispatches)){
            postInfo << "Dispatcher(" << name() << ") sent post (" << msg->metaInfo().name() << ":" << msg->id() 
                << ") to " << cnt << " recipients";
        }
    }

    void        Dispatcher::_dispatching(const PostCPtr&msg, Post::flag_initlist_t auxFlags, bool self)
    {
        if(!msg.valid())
            return ;

        auto& t = thread();
        bool    pushed  = false;

        // Claim ownership if unassigned
        if(!msg->m_originator){
            ++m_balance;
            Post*   p   = const_cast<Post*>(msg.ptr());
            for(Post::flag_t f : auxFlags)
                p->m_flags.set(f);
            p->m_originator   = this;
        }
        
        // Check for circular sending loops
        if(t.postage.empty() || (t.postage.top().msg != msg.ptr())){
            t.postage << Postage(msg.ptr());
            pushed  = true;
        }
        
        _dispatch(msg, self);
        
        if(pushed){
            t.postage.pop();
        }
    }

    void    Dispatcher::_poll(Dispatcher* disp, unit::Second timeout)
    {
        if(m_polling.test_and_set())
            return ;

        auto& t = thread();
        size_t  n = 0;
        if(disp){
            for(; n<t.sockets.size(); ++n){
                if(!t.sockets[n])
                    break;
            }
            if(n>=t.sockets.size()){
                n       = t.sockets.size();
                t.sockets.push_back(disp);
            }
        }
        
        polling(timeout);
        if(disp){
            t.sockets[n]    = nullptr;
        }
        m_polling.clear();
    }

    void    Dispatcher::_receive(const PostCPtr& msg)
    {
        if(m_logging(Log::Receives)){
            postInfo << "Dispatcher(" << name() << ") received post (" << msg->metaInfo().name() << ":" << msg->id() << ")";
        }
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

    void    Dispatcher::add_role(R r)
    {
        m_roles |= r;
    }

    void    Dispatcher::capture(global_t)
    {
        common().sockets.push_back(this);
        m_roles |= R::GlobalCapture;
    }

    Dispatcher::Capture     Dispatcher::capture(thread_t)
    {
        return Capture(this);
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

    std::string_view    Dispatcher::description() const
    {
        if(!m_description.empty())
            return m_description;
            
        if(const Object* obj = dynamic_cast<const Object*>(this)){
            return obj -> metaInfo().description();
        }
        
        return "Generic Post Dispatcher";
    }

    void    Dispatcher::description(std::string_view k)
    {
        m_description   = k;
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


    void        Dispatcher::dispatch(const PostCPtr& msg, Post::flag_initlist_t auxFlags)
    {
        _dispatching(msg, auxFlags, false);
    }

    void        Dispatcher::dispatch(self_t, const PostCPtr&msg, Post::flag_initlist_t auxFlags)
    {
        _dispatching(msg, auxFlags, true);
    }
    
    #if 0
        //! Installs a global snoop (good for event logging)
        //! This is *NOT* thread-safe call, do it at initialization time.  (ie create & set before use)
        static void install(global_t, SnoopFN&&);
        
        void install(SnoopFN&&);
        void install(sender_k, SnoopFN&&);
        void install(receiver_k, SnoopFN&&);
#endif

    void Dispatcher::install(const FilterCPtr& fn)
    {
        if(fn){
            m_filters.push_back(fn);
        }
    }
    
    void Dispatcher::install(sender_k, const FilterCPtr&fn)
    {
        if(fn){
            m_tx.filters.push_back(fn);
        }
    }
    
    void Dispatcher::install(receiver_k, const FilterCPtr&fn)
    {
        if(fn){
            m_rx.filters.push_back(fn);
        }
    }

    std::string_view    Dispatcher::name() const
    {
        if(!m_name.empty())
            return m_name;
            
        if(const Object* obj = dynamic_cast<const Object*>(this)){
            return obj -> metaInfo().name();
        }
        
        return "post::Dispatcher";
    }

    bool    Dispatcher::is_listener() const
    {
        return m_roles(R::Listener);
    }
    
    bool    Dispatcher::is_poller() const
    {
        return m_roles(R::Poller);
    }
    
    bool    Dispatcher::is_global_capture() const
    {
        return m_roles(R::GlobalCapture);
    }

    void    Dispatcher::name(std::string_view k)
    {
        m_name      = k;
    }

    void    Dispatcher::poll(unit::Second timeout)
    {
        _poll(nullptr, timeout);
    }
    
    void    Dispatcher::poll(Dispatcher&disp, unit::Second timeout)
    {
        _poll(&disp, timeout);
    }
}
