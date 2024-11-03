////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "AndTrigger.hpp"
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
    
    void AndTrigger::init_info()
    {
        auto w = writer<AndTrigger>();
        w.description("An AND post trigger based on other triggers");
    }
}
