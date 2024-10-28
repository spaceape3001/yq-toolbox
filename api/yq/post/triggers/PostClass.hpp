////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/post/Trigger.hpp>
#include <yq/post/Post.hpp>

namespace yq::post {
    class PostClassTrigger : public Trigger {
        YQ_OBJECT_DECLARE(PostClassTrigger, Trigger)
    public:
    
        using Param = Trigger::Param;
    
        PostClassTrigger(const PostInfo&, const Param& p = {});
        ~PostClassTrigger();
        bool    accept(const Post&) const;
    
    private:
        const PostInfo&     m_postInfo;
    };
    
    template <SomePost P>
    class PostClass : public PostClassTrigger {
        YQ_OBJECT_DECLARE(PostClass, PostClassTrigger)
    public:
        using post_type = P;
        PostClass(const Param& p = {}) : PostClassTrigger(meta<P>(), p) {}
    };
}
