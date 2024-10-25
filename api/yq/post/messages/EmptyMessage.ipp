////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "EmptyMessage.hpp"
#include <yq/core/DelayInit.hpp>
#include <yq/post/MessageInfoWriter.hpp>

namespace yq::post {
    EmptyMessage::EmptyMessage(const Param& p) : Message(p) 
    {
    }
    
    EmptyMessage::~EmptyMessage()
    {
    }
    
    static void reg_empty_message()
    {
        auto w = writer<EmptyMessage>();
        w.description("Empty Message");
    }
    
    YQ_INVOKE(
        reg_empty_message();
    );
}

YQ_OBJECT_IMPLEMENT(yq::post::EmptyMessage)
