////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/post/Event.hpp>
#include <yq/post/Trigger.hpp>

namespace yq::post {

    class OnEvent : public Trigger {
        YQ_OBJECT_DECLARE(OnEvent, Trigger)
    public:
    
        struct Param : public Trigger::Param {
        };
        
        bool accept(const Event&) const;
        
        template <SomeEvent C = Event>
        OnEvent(const Param& p = {}) : OnEvent(meta<C>(), p) {}
        OnEvent(const EventInfo&, const Param& p={});

    private:
        ~OnEvent();
        const EventInfo&  m_info;
    };
}
