////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "PostBox.hpp"

namespace yq::post {
    PostBox::PostBox(const Param& p) : Dispatcher(p)
    {
        if(p.name.empty())
            name("PostBox");
    }
    
    PostBox::~PostBox()
    {
    }

    void    PostBox::send(const PostCPtr& pp)
    {
        dispatch(pp, { Post::kFlag_Public });
    }
}
