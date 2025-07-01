////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "StringReply.hpp"
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
    
    void StringReply::init_meta()
    {
        auto w = writer<StringReply>();
        w.description("Text Reply");
        w.property("text", &StringReply::text);
    }
}

YQ_OBJECT_IMPLEMENT(yq::post::StringReply)
