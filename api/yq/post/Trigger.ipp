////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Trigger.hpp"
#include <yq/core/DelayInit.hpp>
#include "TriggerInfoWriter.hpp"

YQ_OBJECT_IMPLEMENT(yq::post::Trigger)

namespace yq::post {
    TriggerInfo::TriggerInfo(std::string_view zName, const FilterInfo& base, const std::source_location& sl) :
        FilterInfo(zName, base, sl)
    {
        set(Flag::TRIGGER);
    }
    
    Trigger::Trigger(const Param& p) : Filter(p)
    {
    }
    
    Trigger::~Trigger()
    {
    }

    bool    Trigger::accept(const Dispatcher&, const Dispatcher&, const Post& pp) const 
    {
        return accept(pp);
    }

    static void reg_trigger()
    {
        auto w = writer<Trigger>();
        w.description("Abstract Post Trigger");
    }

    
    YQ_INVOKE(reg_trigger();)
}
