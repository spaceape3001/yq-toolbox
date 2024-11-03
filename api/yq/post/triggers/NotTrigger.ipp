////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "NotTrigger.hpp"
#include <yq/post/TriggerInfoWriter.hpp>

YQ_OBJECT_IMPLEMENT(yq::post::NotTrigger)

namespace yq::post {

    NotTrigger::NotTrigger(const TriggerCPtr& inc, const Param& p) : Trigger(p), m_original(inc)
    {
        assert(m_original);
    }
    
    NotTrigger::~NotTrigger()
    {
    }
    
    bool    NotTrigger::accept(const Post&pp) const 
    {
        if(!m_original)   // shouldn't happen, demo...
            return false;
        return !m_original->passed(pp);
    }

    void NotTrigger::init_info()
    {
        auto w = writer<NotTrigger>();
        w.description("NOT post trigger (ie, negates the given trigger's test)");
    }
}
