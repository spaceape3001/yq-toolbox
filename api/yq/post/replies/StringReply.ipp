////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "StringReply.hpp"
#include <yq/core/DelayInit.hpp>
#include <yq/post/ReplyInfoWriter.hpp>

namespace yq::post {
    StringReply::StringReply(const RequestCPtr&rq, std::string&& k, const Param& p) : Reply(rq, p), m_text(std::move(k))
    {
    }
    
    StringReply::StringReply(const RequestCPtr&rq, const char* k, const Param& p) : Reply(rq, p), m_text(k)
    {
    }
    
    StringReply::StringReply(const RequestCPtr&rq, std::string_view k, const Param& p) : Reply(rq, p), m_text(k)
    {
    }
    
    static void reg_string_reply()
    {
        auto w = writer<StringReply>();
        w.description("Text Reply");
        w.property("text", &StringReply::text);
    }

    
    YQ_INVOKE(
        reg_string_reply();
    );
}

YQ_OBJECT_IMPLEMENT(yq::post::StringReply)
