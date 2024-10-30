////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "AndTrigger.hpp"
#include <yq/core/DelayInit.hpp>
#include <yq/post/TriggerInfoWriter.hpp>

YQ_OBJECT_IMPLEMENT(yq::post::AndTrigger)

namespace yq::post {
    AndTrigger::AndTrigger(std::initializer_list<TriggerCPtr> triggers, const Param&p) : Trigger(p), m_triggers(triggers.begin(), triggers.end())
    {
    }
    
    AndTrigger::~AndTrigger()
    {
    }

    bool    AndTrigger::accept(const Post& pp) const 
    {
        for(const TriggerCPtr& f : m_triggers){
            if(f && !f->passed(pp))
                return false;
        }
        return true;
    }
    
    static void reg_and_trigger()
    {
        auto w = writer<AndTrigger>();
        w.description("An AND post trigger based on other triggers");
    }
    
    YQ_INVOKE(reg_and_trigger();)
}
