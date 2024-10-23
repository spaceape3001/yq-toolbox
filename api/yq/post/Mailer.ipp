////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Mailer.hpp"
#include <yq/container/Stack.hpp>
#include <yq/core/Object.hpp>
#include <stack>

namespace yq::post {

    //  Used to keep track of messages en-route to stop circular dependencies
    struct Mailer::Postage {
        Post*            msg     = nullptr;
        std::set<Mailer*>      seen;
        
        Postage() {}
        Postage(Post* m, Mailer* b) : msg(m)
        {
            seen.insert(b);
        }
        
        bool    first(Mailer* b)
        {
            auto [i,f]  = seen.insert(b);
            return f;
        }
    };

    ////////////////////////////////////////////////////////////////////////////

    struct Mailer::Thread {
        Stack<Postage>      postage;
        std::vector<Mailer*>   sockets;
        
        void    capture(Mailer* mbx)
        {
            if(!mbx)
                return ;
            sockets.push_back(mbx);
        }
        
        void    uncapture(Mailer* mbx)
        {
            if(!mbx)
                return ;
            
            auto itr = std::find(sockets.rbegin(), sockets.rend(), mbx);
            if(itr == sockets.rend())
                return ;
            sockets.erase(itr.base());
        }
    };
    
    Mailer::Thread&    Mailer::thread()
    {
        static thread_local Thread s_ret;
        return s_ret;
    }

    ////////////////////////////////////////////////////////////////////////////
    
    Mailer::Capture::Capture(Mailer*mbx) : m_box(mbx)
    {
        thread().capture(mbx);
    }

    Mailer::Capture::Capture()
    {
    }
    
    Mailer::Capture::~Capture()
    {
        thread().uncapture(m_box);
    }

    Mailer::Capture::Capture(Capture&&mv) : m_box(mv.m_box)
    {
        mv.m_box    = nullptr;
    }
    
    Mailer::Capture& Mailer::Capture::operator=(Capture&& mv)
    {
        if(this != &mv){
            thread().uncapture(m_box);
            m_box       = mv.m_box;
            mv.m_box    = nullptr;
        }
        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////

    Mailer::Connection::Connection(Mailer* tx, Mailer* rx) : m_sender(tx), m_recipient(rx)
    {
    }

    Mailer::Connection::~Connection()
    {
        for(Filter* f : m_filters)
            delete f;
        m_filters.clear();
    }

    bool    Mailer::Connection::accept(const Post&msg) const
    {   
        for(const Filter* f : m_filters){
            if(!f->accept(msg))
                return false;
        }
        return true;
    }
    
    ////////////////////////////////////////////////////////////////////////////

    void    Mailer::Queue::_forget(Connection*c)
    {
        std::erase(connections, c);
    }


    ////////////////////////////////////////////////////////////////////////////

    Mailer::Mailer()
    {
    }
    
    Mailer::~Mailer()
    {
        unsubscribe(ALL);
    }

    void    Mailer::_receive(PostPtr msg)
    {
        receive(msg);
        ++(m_rx.usage);
    }
    
    void    Mailer::_send(PostPtr msg)
    {
        Thread& t = thread();
        for(Mailer* b : t.sockets){
            b -> _receive(msg);
        }
        for(Connection* c : m_tx.connections){
            if(!c->accept(*msg))
                continue;
            c -> m_recipient -> _receive(msg);
        }
        ++(m_tx.usage);
    }

    Mailer::Capture     Mailer::capture(all_t)
    {
        return Capture(this);
    }

    std::string_view    Mailer::description() const
    {
        if(const Object* obj = dynamic_cast<const Object*>(this)){
            return obj -> metaInfo().description();
        }
        
        return "Generic Post Mailer";
    }

    std::string_view    Mailer::name() const
    {
        if(const Object* obj = dynamic_cast<const Object*>(this)){
            return obj -> metaInfo().name();
        }
        
        return "post::Mailer";
    }

    void        Mailer::publish(PostPtr msg)
    {
        if(!msg.valid())
            return ;
            
        auto& t = thread();
        bool    pushed  = false;

        // Claim ownership if unassigned
        if(!msg->m_originator){
            ++m_balance;
            msg->m_originator   = this;
        }
        
        // Check for circular sending loops
        if(t.postage.empty() || (t.postage.top().msg != msg.ptr())){
            t.postage << Postage(msg.ptr(), this);
            pushed  = true;
        } else {
            if(!t.postage.top().first(this)){
                // duplicate, bye
                return ;
            }
        }

        _send(msg);
        
        if(pushed){
            t.postage.pop();
        }
    }

    Mailer::Connection&     Mailer::subscribe(pull_t, Mailer& sender)
    {
        return sender.subscribe(PUSH, *this);
    }

    Mailer::Connection&     Mailer::subscribe(push_t, Mailer& recipient)
    {
        Connection* c   = new Connection(this, &recipient);
        m_tx.connections.push_back(c);
        recipient.m_rx.connections.push_back(c);
        return *c;
    }

    void    Mailer::unsubscribe(pull_t, Mailer& sender)
    {
        // TODO
    }

    void    Mailer::unsubscribe(push_t, Mailer& recipient)
    {
        // TODO
    }

    void    Mailer::unsubscribe(Mailer& other)
    {
        // TODO
    }

    void    Mailer::unsubscribe(all_t)
    {
        // TODO
    }

    void    Mailer::unsubscribe(push_t, all_t)
    {
        // TODO
    }

    void    Mailer::unsubscribe(pull_t, all_t)
    {
        // TODO
    }
}
