////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "PostClass.hpp"
#include <yq/core/DelayInit.hpp>
#include <yq/post/TriggerInfoWriter.hpp>

YQ_OBJECT_IMPLEMENT(yq::post::PostClassTrigger)

namespace yq::post {
    PostClassTrigger::PostClassTrigger(const PostInfo& info, const Param& p) : Trigger(p), m_postInfo(info)
    {
    }
    
    PostClassTrigger::~PostClassTrigger()
    {
    }
    
    bool    PostClassTrigger::accept(const Post&pp) const 
    {
        return m_postInfo.is_derived(pp.metaInfo());
    }

    static void reg_generic_post_trigger()
    {
        auto w = writer<PostClassTrigger>();
        w.description("Trigger based on the post type");
    }
    
    YQ_INVOKE(reg_generic_post_trigger();)
}
