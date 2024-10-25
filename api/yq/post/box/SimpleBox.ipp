////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "SimpleBox.hpp"

namespace yq::post {
    SimpleBox::SimpleBox(const Param& p) : Dispatcher(p)
    {
        if(p.name.empty())
            name("SimpleBox");
    }
    
    SimpleBox::~SimpleBox()
    {
    }

    void    SimpleBox::receive(const PostCPtr&pp) 
    {
        m_posts.push_back(pp);
    }

    void    SimpleBox::send(const PostCPtr& pp)
    {
        dispatch(pp, { Post::kFlag_Public });
    }
}
