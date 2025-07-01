////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "EmptyPost.hpp"
#include <yq/post/PostInfoWriter.hpp>

namespace yq::post {
    EmptyPost::EmptyPost(const Param& p) : Post(p) 
    {
    }
    
    EmptyPost::~EmptyPost()
    {
    }
    
    void EmptyPost::init_meta()
    {
        auto w = writer<EmptyPost>();
        w.description("Empty Post");
    }
}

YQ_OBJECT_IMPLEMENT(yq::post::EmptyPost)
