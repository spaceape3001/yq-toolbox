////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "OnCommand.hpp"
#include <yq/post/TriggerInfoWriter.hpp>

YQ_OBJECT_IMPLEMENT(yq::post::OnCommand)

namespace yq::post {

    OnCommand::OnCommand(const CommandInfo& cInfo, const Param& p) : Trigger(p), m_info(cInfo)
    {
    }
    
    OnCommand::~OnCommand()
    {
    }
    
    bool OnCommand::accept(const Command& cmd) const
    {
        const CommandInfo& cInfo    = cmd.metaInfo();
        return (&cInfo == &m_info) || cInfo.is_base(m_info);
    }
    
    void OnCommand::init_info()
    {
        auto w = writer<OnCommand>();
        w.description("Trigger for a particular command class");
    }
}
