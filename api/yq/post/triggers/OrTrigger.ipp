////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "OrTrigger.hpp"
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
            if(f && f->passed(pp))
                return true;
        }
        return false;
    }
    
    void OrTrigger::init_meta()
    {
        auto w = writer<OrTrigger>();
        w.description("An OR post trigger based on other triggers");
    }
}
