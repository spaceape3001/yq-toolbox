////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "EmptyPost.hpp"
#include <yq/core/DelayInit.hpp>
#include <yq/post/PostInfoWriter.hpp>

namespace yq::post {
    EmptyPost::EmptyPost(const Param& p) : Post(p) 
    {
    }
    
    EmptyPost::~EmptyPost()
    {
    }
    
    static void reg_empty_post()
    {
        auto w = writer<EmptyPost>();
        w.description("Empty Post");
    }
    
    YQ_INVOKE(
        reg_empty_post();
    );
}

YQ_OBJECT_IMPLEMENT(yq::post::EmptyPost)
