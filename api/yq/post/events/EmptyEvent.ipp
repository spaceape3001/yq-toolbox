////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "EmptyEvent.hpp"
#include <yq/core/DelayInit.hpp>
#include <yq/post/EventInfoWriter.hpp>

namespace yq::post {
    EmptyEvent::EmptyEvent(const Param& p) : Event(p) 
    {
    }
    
    EmptyEvent::~EmptyEvent()
    {
    }
    
    static void reg_empty_event()
    {
        auto w = writer<EmptyEvent>();
        w.description("Empty Event");
    }
    
    YQ_INVOKE(
        reg_empty_event();
    );
}

YQ_OBJECT_IMPLEMENT(yq::post::EmptyEvent)
