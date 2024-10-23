////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "AnyPost.hpp"
#include <yq/core/DelayInit.hpp>
#include <yq/post/PostInfoWriter.hpp>

namespace yq::post {
    void    AnyPost::init_info()
    {
        auto w = writer<AnyPost>();
        w.description("Any Post");
        w.property("value", &AnyPost::value);
    }

    AnyPost::AnyPost(const Any& val, const Param&p) : Post(p), m_value(val)
    {
    }
    
    AnyPost::AnyPost(Any&& val, const Param&p) : Post(p), m_value(std::move(val))
    {
    }
    
    AnyPost::~AnyPost()
    {
    }

    YQ_INVOKE(
        AnyPost::init_info();
    );
}

YQ_OBJECT_IMPLEMENT(yq::post::AnyPost)
