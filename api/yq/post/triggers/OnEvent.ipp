////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "OnEvent.hpp"
#include <yq/post/TriggerInfoWriter.hpp>

YQ_OBJECT_IMPLEMENT(yq::post::OnEvent)

namespace yq::post {

    OnEvent::OnEvent(const EventInfo& cInfo, const Param& p) : Trigger(p), m_info(cInfo)
    {
    }
    
    OnEvent::~OnEvent()
    {
    }
    
    bool OnEvent::accept(const Event& cmd) const
    {
        const EventInfo& cInfo    = cmd.metaInfo();
        return (&cInfo == &m_info) || cInfo.is_base(m_info);
    }
    
    void OnEvent::init_info()
    {
        auto w = writer<OnEvent>();
        w.description("Trigger for a particular event class");
    }
    
}
