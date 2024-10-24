////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/post/Post.hpp>

namespace yq::post {

    class CommandInfo : public PostInfo {
    public:
        template <typename C> class Writer;

        CommandInfo(std::string_view zName, const PostInfo& base, const std::source_location& sl=std::source_location::current());
    };

    class Command : public Post {
        YQ_OBJECT_INFO(CommandInfo)
        YQ_OBJECT_DECLARE(Command, Post)
    public:
   
        struct Param : public Post::Param {
        };
        
        virtual ~Command();
        
    protected:
        Command(const Param&);
    };
}
