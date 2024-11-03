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

        EventInfo(std::string_view zName, PostInfo& base, const std::source_location& sl=std::source_location::current());
    };

    class Event : public Post {
        YQ_OBJECT_INFO(EventInfo)
        YQ_OBJECT_DECLARE(Event, Post)
        template <class> friend class Ref;
    public:
    
        struct Param : public Post::Param {
        };
        
        static void init_info();
        
    protected:
        virtual ~Event();
        Event(const Param& p={});
    };
}
