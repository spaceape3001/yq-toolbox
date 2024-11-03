////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Request.hpp"
#include "RequestInfoWriter.hpp"

YQ_OBJECT_IMPLEMENT(yq::post::Request)

namespace yq::post {
    RequestInfo::RequestInfo(std::string_view zName, PostInfo& base, const std::source_location& sl) :
        PostInfo(zName, base, sl)
    {
        set(Flag::REQUEST);
    }

    ////////////////////////////////////////////////////////////////////////////

    Request::Request(const Param& p) : Post(p)
    {
    }
    
    Request::~Request()
    {
    }


    ////////////////////////////////////////////////////////////////////////////

    void Request::init_info()
    {
        auto w = writer<Request>();
        w.description("Abstract Request Class");
    }
}
