////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "EmptyReply.hpp"
#include <yq/post/ReplyInfoWriter.hpp>

namespace yq::post {
    EmptyReply::EmptyReply(const RequestCPtr& rq, const Param& p) : Reply(rq, p) 
    {
    }
    
    EmptyReply::~EmptyReply()
    {
    }
    
    void EmptyReply::init_info()
    {
        auto w = writer<EmptyReply>();
        w.description("Empty Reply");
    }
}

YQ_OBJECT_IMPLEMENT(yq::post::EmptyReply)
