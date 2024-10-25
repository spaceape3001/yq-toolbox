////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/post/Post.hpp>

namespace yq::post {

    //! Test/general post type that's empty
    class EmptyPost : public Post {
        YQ_OBJECT_DECLARE(EmptyPost, Post)
    public:
        
        //  contributing nothing extra....
        using Post::Param;
        
        EmptyPost(const Param& p = {});
        ~EmptyPost();
    };
}
