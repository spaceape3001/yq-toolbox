////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/post/Event.hpp>

namespace yq::post {

    //! Test/general post type that's empty
    class EmptyEvent : public Event {
        YQ_OBJECT_DECLARE(EmptyEvent, Event)
    public:
        
        //  contributing nothing extra....
        using Event::Param;
        
        EmptyEvent(const Param& p = {});
        ~EmptyEvent();
        
        static void init_info();
    };
}
