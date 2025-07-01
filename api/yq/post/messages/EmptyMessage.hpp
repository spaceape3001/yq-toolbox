////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/post/Message.hpp>

namespace yq::post {

    //! Test/general post type that's empty
    class EmptyMessage : public Message {
        YQ_OBJECT_DECLARE(EmptyMessage, Message)
    public:
        
        //  contributing nothing extra....
        using Message::Param;
        
        EmptyMessage(const Param& p = {});
        ~EmptyMessage();
        
        static void init_meta();
    };
}
