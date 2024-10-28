////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/post/Request.hpp>
#include <yq/post/Trigger.hpp>

namespace yq::post {

    class OnRequest : public Trigger {
        YQ_OBJECT_DECLARE(OnRequest, Trigger)
    public:
    
        struct Param : public Trigger::Param {
        };
        
        bool accept(const Request&) const;
        
        template <SomeRequest C = Request>
        OnRequest(const Param& p = {}) : OnRequest(meta<C>(), p) {}
        OnRequest(const RequestInfo&, const Param& p={});

    private:
        ~OnRequest();
        const RequestInfo&  m_info;
    };
}
