////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/post/Post.hpp>

namespace yq::post {
    class MessageInfo : public PostInfo {
    public:
        template <typename C> class Writer;

        MessageInfo(std::string_view zName, const PostInfo& base, const std::source_location& sl=std::source_location::current());
    };
    
    /*! \brief Light weight message
    
        More informational, message to another?  Right now, 
        the Message class is "generic", though it may morph.
    */
    class Message : public Post {
        YQ_OBJECT_INFO(MessageInfo)
        YQ_OBJECT_DECLARE(Message, Post)
        template <class> friend class Ref;
    public:
    
        struct Param : public Post::Param {
        };
    
    protected:

        Message(const Param&);
        virtual ~Message();
    };
}
