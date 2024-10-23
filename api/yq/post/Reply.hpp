////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/typedef/event.hpp>
#include <yq/typedef/request.hpp>
#include <yq/post/Post.hpp>

namespace yq::post {
    class ReplyInfo : public PostInfo {
    public:
        template <typename C> class Writer;

        ReplyInfo(std::string_view zName, const PostInfo& base, const std::source_location& sl=std::source_location::current());
    };

    class Reply : public Post {
        YQ_OBJECT_INFO(ReplyInfo)
        YQ_OBJECT_DECLARE(Reply, Post)
    public:
   
        struct Param : public Post::Param {
        };
        
        virtual ~Reply();
        
        const Request*  request() const;
        
    protected:
        Reply(RequestCPtr, const Param&);
        
    private:
        RequestCPtr     m_request;
    };
}
