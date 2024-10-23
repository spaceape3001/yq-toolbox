////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/post/Post.hpp>

namespace yq::post {

    //! Test post type that's empty
    class EmptyPost : public Post {
        YQ_OBJECT_DECLARE(EmptyPost, Post)
    public:
    
        static void init_info();
        
        //  contributing nothing extra....
        using Post::Param;
        
        EmptyPost(const Param& p = {});
        ~EmptyPost();
    };
}
