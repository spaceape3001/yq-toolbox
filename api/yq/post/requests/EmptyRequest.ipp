////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "EmptyRequest.hpp"
#include <yq/core/DelayInit.hpp>
#include <yq/post/RequestInfoWriter.hpp>

namespace yq::post {
    EmptyRequest::EmptyRequest(const Param& p) : Request(p) 
    {
    }
    
    EmptyRequest::~EmptyRequest()
    {
    }
    
    static void reg_empty_request()
    {
        auto w = writer<EmptyRequest>();
        w.description("Empty Request");
    }
    
    YQ_INVOKE(
        reg_empty_request();
    );
}

YQ_OBJECT_IMPLEMENT(yq::post::EmptyRequest)
