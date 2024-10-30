////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Reply.hpp"
#include "ReplyInfoWriter.hpp"
#include <yq/post/Request.hpp>
#include <yq/core/DelayInit.hpp>

YQ_OBJECT_IMPLEMENT(yq::post::Reply)

namespace yq::post {
    ReplyInfo::ReplyInfo(std::string_view zName, PostInfo& base, const std::source_location& sl) :
        PostInfo(zName, base, sl)
    {
        set(Flag::REPLY);
    }

    ////////////////////////////////////////////////////////////////////////////

    Reply::Reply(const RequestCPtr& req, const Param& p) : Post(p), m_request(req)
    {
    }
    
    Reply::~Reply()
    {
    }

    const Request*  Reply::request() const
    {
        return m_request.ptr();
    }

    ////////////////////////////////////////////////////////////////////////////

    static void reg_reply()
    {
        auto w = writer<Reply>();
        w.description("Abstract Reply Class");
    }
    
    YQ_INVOKE(reg_reply();)
}
