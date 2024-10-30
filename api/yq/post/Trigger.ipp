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
    TriggerInfo::TriggerInfo(std::string_view zName, FilterInfo& base, const std::source_location& sl) :
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

    FilterResult    Trigger::check(const Post& pp) const
    {
        return metaInfo().accept(*this, pp);
    }

    MismatchPolicy  Trigger::mismatch() const
    {
        return m_mismatch(MismatchType::InPost) ? MismatchPolicy::Accept : MismatchPolicy::Reject;
    }

    bool    Trigger::passed(const Post& pp) const
    {
        FilterResult    chk  = check(pp);
        if(auto p = std::get_if<bool>(&chk))
            return *p;
        if(auto p = std::get_if<MismatchFlags>(&chk))
            return (*p - m_mismatch) == MismatchFlags();
        return false;   // should never hit here
    }

    static void reg_trigger()
    {
        auto w = writer<Trigger>();
        w.description("Abstract Post Trigger");
    }

    
    YQ_INVOKE(reg_trigger();)
}
