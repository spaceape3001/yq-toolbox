////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/post/Post.hpp>

namespace yq::post {

    class EventInfo : public PostInfo {
    public:
        template <typename C> class Writer;

        EventInfo(std::string_view zName, const PostInfo& base, const std::source_location& sl=std::source_location::current());
    };

    class Event : public Post {
        YQ_OBJECT_INFO(EventInfo)
        YQ_OBJECT_DECLARE(Event, Post)
    public:
    
        struct Param : public Post::Param {
        };
        
        virtual ~Event();
        
    protected:
        Event(const Param&);
    };
}
