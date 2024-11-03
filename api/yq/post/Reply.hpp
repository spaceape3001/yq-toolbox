////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/post/Post.hpp>

namespace yq::post {
    class ReplyInfo : public PostInfo {
    public:
        template <typename C> class Writer;

        ReplyInfo(std::string_view zName, PostInfo& base, const std::source_location& sl=std::source_location::current());
    };

    class Reply : public Post {
        YQ_OBJECT_INFO(ReplyInfo)
        YQ_OBJECT_DECLARE(Reply, Post)
        template <class> friend class Ref;
    public:
   
        struct Param : public Post::Param {
        };
        
        const Request*  request() const;
        
        static void init_info();
        
    protected:
        Reply(const RequestCPtr&, const Param& p={});
        virtual ~Reply();
        
    private:
        RequestCPtr     m_request;
    };
}
