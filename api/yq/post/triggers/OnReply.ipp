////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "OnReply.hpp"
#include <yq/post/TriggerInfoWriter.hpp>

YQ_OBJECT_IMPLEMENT(yq::post::OnReply)

namespace yq::post {

    OnReply::OnReply(const ReplyInfo& cInfo, const Param& p) : Trigger(p), m_info(cInfo)
    {
    }
    
    OnReply::~OnReply()
    {
    }
    
    bool OnReply::accept(const Reply& cmd) const
    {
        const ReplyInfo& cInfo    = cmd.metaInfo();
        return (&cInfo == &m_info) || cInfo.is_base(m_info);
    }
    
    void OnReply::init_meta()
    {
        auto w = writer<OnReply>();
        w.description("Trigger for a particular reply class");
    }
}
