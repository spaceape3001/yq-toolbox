////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "EmptyMessage.hpp"
#include <yq/post/MessageInfoWriter.hpp>

namespace yq::post {
    EmptyMessage::EmptyMessage(const Param& p) : Message(p) 
    {
    }
    
    EmptyMessage::~EmptyMessage()
    {
    }
    
    void EmptyMessage::init_meta()
    {
        auto w = writer<EmptyMessage>();
        w.description("Empty Message");
    }
}

YQ_OBJECT_IMPLEMENT(yq::post::EmptyMessage)
