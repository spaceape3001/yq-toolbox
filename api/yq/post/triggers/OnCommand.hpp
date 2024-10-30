////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/post/Command.hpp>
#include <yq/post/Trigger.hpp>

namespace yq::post {

    class OnCommand : public Trigger {
        YQ_OBJECT_DECLARE(OnCommand, Trigger)
    public:
    
        struct Param : public Trigger::Param {
        };
        
        bool accept(const Command&) const;
        
        template <SomeCommand C = Command>
        OnCommand(const Param& p = {}) : OnCommand(meta<C>(), p) {}
        OnCommand(const CommandInfo&, const Param& p={});

    private:
        ~OnCommand();
        const CommandInfo&  m_info;
    };
}
