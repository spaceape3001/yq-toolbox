////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "AnyPost.hpp"
#include <yq/core/DelayInit.hpp>
#include <yq/post/PostInfoWriter.hpp>

namespace yq::post {
    AnyPost::AnyPost(const Any& val, const Param&p) : Post(p), m_value(val)
    {
    }
    
    AnyPost::AnyPost(Any&& val, const Param&p) : Post(p), m_value(std::move(val))
    {
    }
    
    AnyPost::~AnyPost()
    {
    }

    static void reg_any_post()
    {
        auto w = writer<AnyPost>();
        w.description("Any Post");
        w.property("value", &AnyPost::value);
    }

    YQ_INVOKE(
        reg_any_post();
    );
}

YQ_OBJECT_IMPLEMENT(yq::post::AnyPost)
