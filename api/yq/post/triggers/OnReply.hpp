////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/post/Reply.hpp>
#include <yq/post/Trigger.hpp>

namespace yq::post {

    class OnReply : public Trigger {
        YQ_OBJECT_DECLARE(OnReply, Trigger)
    public:
    
        struct Param : public Trigger::Param {
        };
        
        bool accept(const Reply&) const;
        
        template <SomeReply C = Reply>
        OnReply(const Param& p = {}) : OnReply(meta<C>(), p) {}
        OnReply(const ReplyInfo&, const Param& p={});

    private:
        ~OnReply();
        const ReplyInfo&  m_info;
    };
}
