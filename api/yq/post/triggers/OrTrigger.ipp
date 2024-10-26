////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "OrTrigger.hpp"
#include <yq/core/DelayInit.hpp>
#include <yq/post/TriggerInfoWriter.hpp>

YQ_OBJECT_IMPLEMENT(yq::post::OrTrigger)

namespace yq::post {
    OrTrigger::OrTrigger(std::initializer_list<TriggerCPtr> triggers, const Param&p) : Trigger(p), m_triggers(triggers.begin(), triggers.end())
    {
    }
    
    OrTrigger::~OrTrigger()
    {
    }

    bool    OrTrigger::accept(const Post& pp) const 
    {
        for(const TriggerCPtr& f : m_triggers){
            if(f && f->accept(pp))
                return true;
        }
        return false;
    }
    
    static void reg_or_trigger()
    {
        auto w = writer<OrTrigger>();
        w.description("An OR post trigger based on other triggers");
    }
    
    YQ_INVOKE(reg_or_trigger();)
}
