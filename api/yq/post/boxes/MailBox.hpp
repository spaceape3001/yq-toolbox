////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/post/Dispatcher.hpp>
#include <tbb/spin_rw_mutex.h>

namespace yq::post {
    /*! \brief Multithreaded mailbox
    */
    class MailBox : public Dispatcher {
    public:
        using Param = Dispatcher::Param;
        
        MailBox(const Param& p=Param());
        ~MailBox();
        
        // Picks up ALL the current posts
        std::vector<PostCPtr>   posts(pickup_t);
        
        /*! \brief Gets the number of items in the mailbox
            \note We're multithreaded and this involves a mutex lock, 
            so if you're picking up, pick up, cost is the same.
        */
        size_t  posts(count_t) const;
        bool    posts(empty_t) const;
        
        void    send(const PostCPtr&);
        
    protected:
        void    receive(const PostCPtr&) override;
        
    private:
        using mutex_t   = tbb::spin_rw_mutex;
        using lock_t    = typename mutex_t::scoped_lock;
    
        std::vector<PostCPtr>   m_posts;
        mutable mutex_t         m_mutex;
    };
}
