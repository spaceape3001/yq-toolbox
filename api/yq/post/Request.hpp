////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/post/Post.hpp>

namespace yq::post {

    class RequestInfo : public PostInfo {
    public:
        template <typename C> class Writer;

        RequestInfo(std::string_view zName, PostInfo& base, const std::source_location& sl=std::source_location::current());
    };

    class Request : public Post {
        YQ_OBJECT_INFO(RequestInfo)
        YQ_OBJECT_DECLARE(Request, Post)
        template <class> friend class Ref;
    public:
    
        struct Param : public Post::Param {
        };
        
        static void init_info();
        
    protected:
        Request(const Param& p={});
        virtual ~Request();
    };
}
