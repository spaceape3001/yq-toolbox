////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/typedef/request.hpp>
#include <yq/post/Post.hpp>

namespace yq::post {

    class RequestInfo : public PostInfo {
    public:
        template <typename C> class Writer;

        RequestInfo(std::string_view zName, const PostInfo& base, const std::source_location& sl=std::source_location::current());
    };

    class Request : public Post {
        YQ_OBJECT_INFO(RequestInfo)
        YQ_OBJECT_DECLARE(Request, Post)
    public:
    
        struct Param : public Post::Param {
        };
        
        virtual ~Request();
        
    protected:
        Request(const Param&);
    };
}
