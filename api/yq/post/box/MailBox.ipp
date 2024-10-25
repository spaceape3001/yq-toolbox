////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "MailBox.hpp"

namespace yq::post {
    MailBox::MailBox(const Param& p) : Dispatcher(p)
    {
        if(p.name.empty())
            name("MailBox");
    }
    
    MailBox::~MailBox()
    {
    }
    
    std::vector<PostCPtr>   MailBox::pickup()
    {
        std::vector<PostCPtr> ret;
        {
            lock_t  _lock(m_mutex, true);
            std::swap(ret, m_posts);
        }
        return ret;
    }
    
    size_t  MailBox::size() const
    {
        lock_t  _lock(m_mutex, false);
        return m_posts.size();
    }
    
    
    bool    MailBox::empty() const
    {
        lock_t  _lock(m_mutex, false);
        return m_posts.empty();
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
