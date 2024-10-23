////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "EmptyPost.hpp"
#include <yq/core/DelayInit.hpp>
#include <yq/post/PostInfoWriter.hpp>

namespace yq::post {
    void EmptyPost::init_info()
    {
        auto w = writer<EmptyPost>();
        w.description("Empty Post");
    }

    EmptyPost::EmptyPost(const Param& p) : Post(p) 
    {
    }
    
    EmptyPost::~EmptyPost()
    {
    }
    
    YQ_INVOKE(
        EmptyPost::init_info();
    );
}

YQ_OBJECT_IMPLEMENT(yq::post::EmptyPost)
