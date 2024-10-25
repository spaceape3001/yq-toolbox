////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "EmptyReply.hpp"
#include <yq/core/DelayInit.hpp>
#include <yq/post/ReplyInfoWriter.hpp>

namespace yq::post {
    EmptyReply::EmptyReply(const RequestCPtr& rq, const Param& p) : Reply(rq, p) 
    {
    }
    
    EmptyReply::~EmptyReply()
    {
    }
    
    static void reg_empty_post()
    {
        auto w = writer<EmptyReply>();
        w.description("Empty Reply");
    }
    
    YQ_INVOKE(
        reg_empty_post();
    );
}

YQ_OBJECT_IMPLEMENT(yq::post::EmptyReply)
