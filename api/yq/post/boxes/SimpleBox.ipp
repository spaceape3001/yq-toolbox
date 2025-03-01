////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "SimpleBox.hpp"

namespace yq::post {
    SimpleBox::SimpleBox(const Param& p) : Dispatcher(p, { R::Listener })
    {
        if(p.name.empty())
            name("SimpleBox");
    }
    
    SimpleBox::~SimpleBox()
    {
    }

    std::vector<PostCPtr>   SimpleBox::posts(pickup_t)
    {
        std::vector<PostCPtr> ret;
        std::swap(ret, m_posts);
        return ret;
    }

    size_t      SimpleBox::posts(count_t) const
    {
        return m_posts.size();
    }
    
    bool        SimpleBox::posts(empty_t) const
    {
        return m_posts.empty();
    }
    
    void    SimpleBox::receive(const PostCPtr&pp) 
    {
        if(!pp)
            return ;
        m_posts.push_back(pp);
    }

    void    SimpleBox::send(const PostCPtr& pp)
    {
        if(!pp)
            return ;
        dispatch(pp, { Post::kFlag_Public });
    }
}
