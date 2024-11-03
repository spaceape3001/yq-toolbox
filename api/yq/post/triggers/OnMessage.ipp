////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "OnMessage.hpp"
#include <yq/post/TriggerInfoWriter.hpp>

YQ_OBJECT_IMPLEMENT(yq::post::OnMessage)

namespace yq::post {

    OnMessage::OnMessage(const MessageInfo& cInfo, const Param& p) : Trigger(p), m_info(cInfo)
    {
    }
    
    OnMessage::~OnMessage()
    {
    }
    
    bool OnMessage::accept(const Message& cmd) const
    {
        const MessageInfo& cInfo    = cmd.metaInfo();
        return (&cInfo == &m_info) || cInfo.is_base(m_info);
    }
    
    void OnMessage::init_info()
    {
        auto w = writer<OnMessage>();
        w.description("Trigger for a particular message class");
    }
}
