////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/post/Message.hpp>
#include <yq/post/Trigger.hpp>

namespace yq::post {

    class OnMessage : public Trigger {
        YQ_OBJECT_DECLARE(OnMessage, Trigger)
    public:
    
        struct Param : public Trigger::Param {
        };
        
        bool accept(const Message&) const;
        
        template <SomeMessage C = Message>
        OnMessage(const Param& p = {}) : OnMessage(meta<C>(), p) {}
        OnMessage(const MessageInfo&, const Param& p={});

    private:
        ~OnMessage();
        const MessageInfo&  m_info;
    };
}
