////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/post/Dispatcher.hpp>

namespace yq::post {

    /*! \brief Simple SINGLE THREADED mailbox
    
        This is a box meant for a single threaded-like environment.
        Yes, if you're in the same thread, you can capture everything 
        on that same thread.
    */
    class SimpleBox : public Dispatcher {
    public:
    
        using Param = Dispatcher::Param;
    
        SimpleBox(const Param& p = Param());
        ~SimpleBox();
        
        const std::vector<PostCPtr>& posts() const { return m_posts; }
        
        void        send(const PostCPtr&);
        
        std::vector<PostCPtr>   posts(pickup_t);
        size_t      posts(count_t) const;
        bool        posts(empty_t) const;
        
    protected:
        void    receive(const PostCPtr&) override;
        
    private:
        std::vector<PostCPtr>   m_posts;
    };

}
