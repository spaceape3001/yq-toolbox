////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Event.hpp"
#include "EventInfoWriter.hpp"
#include <yq/core/DelayInit.hpp>

YQ_OBJECT_IMPLEMENT(yq::post::Event)

namespace yq::post {
    EventInfo::EventInfo(std::string_view zName, const PostInfo& base, const std::source_location& sl) :
        PostInfo(zName, base, sl)
    {
        set(Flag::EVENT);
    }

    ////////////////////////////////////////////////////////////////////////////

    Event::Event(const Param& p) : Post(p)
    {
    }
    
    Event::~Event()
    {
    }


    ////////////////////////////////////////////////////////////////////////////

    static void reg_event()
    {
        auto w = writer<Event>();
        w.description("Abstract Event Class");
    }
    
    YQ_INVOKE(reg_event();)
}
