////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "MailBox.hpp"

namespace yq::post {
    MailBox::MailBox(const Param& p) : Dispatcher(p, { R::Listener })
    {
        if(p.name.empty())
            name("MailBox");
    }
    
    MailBox::~MailBox()
    {
    }
    
    size_t  MailBox::posts(count_t) const
    {
        lock_t  _lock(m_mutex, false);
        return m_posts.size();
    }
    
    bool    MailBox::posts(empty_t) const
    {
        lock_t  _lock(m_mutex, false);
        return m_posts.empty();
    }
    
    std::vector<PostCPtr>   MailBox::posts(pickup_t)
    {
        std::vector<PostCPtr> ret;
        {
            lock_t  _lock(m_mutex, true);
            std::swap(ret, m_posts);
        }
        return ret;
    }
    
    void    MailBox::send(const PostCPtr& pp)
    {
        dispatch(pp, { Post::kFlag_Public });
    }
    
    void    MailBox::receive(const PostCPtr&pp) 
    {
        lock_t  _lock(m_mutex, true);
        m_posts.push_back(pp);
    }
}
