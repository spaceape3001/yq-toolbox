////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "EmptyRequest.hpp"
#include <yq/post/RequestInfoWriter.hpp>

namespace yq::post {
    EmptyRequest::EmptyRequest(const Param& p) : Request(p) 
    {
    }
    
    EmptyRequest::~EmptyRequest()
    {
    }
    
    void EmptyRequest::init_meta()
    {
        auto w = writer<EmptyRequest>();
        w.description("Empty Request");
    }
}

YQ_OBJECT_IMPLEMENT(yq::post::EmptyRequest)
