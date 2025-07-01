////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/post/Post.hpp>
#include <yq/post/Trigger.hpp>

namespace yq::post {

    class OnPost : public Trigger {
        YQ_OBJECT_DECLARE(OnPost, Trigger)
    public:
    
        struct Param : public Trigger::Param {
        };
        
        bool accept(const Post&) const;
        
        template <SomePost C = Post>
        OnPost(const Param& p = {}) : OnPost(meta<C>(), p) {}
        OnPost(const PostInfo&, const Param& p={});

        static void init_meta();

    private:
        ~OnPost();
        const PostInfo&  m_info;
    };
}
