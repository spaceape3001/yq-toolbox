////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "OnPost.hpp"
#include <yq/core/DelayInit.hpp>
#include <yq/post/TriggerInfoWriter.hpp>

YQ_OBJECT_IMPLEMENT(yq::post::OnPost)

namespace yq::post {

    OnPost::OnPost(const PostInfo& cInfo, const Param& p) : Trigger(p), m_info(cInfo)
    {
    }
    
    OnPost::~OnPost()
    {
    }
    
    bool OnPost::accept(const Post& cmd) const
    {
        const PostInfo& cInfo    = cmd.metaInfo();
        return (&cInfo == &m_info) || cInfo.is_base(m_info);
    }
    
    static void reg_on_post()
    {
        auto w = writer<OnPost>();
        w.description("Trigger for a particular post class");
    }
    
    YQ_INVOKE(reg_on_post();)
}
