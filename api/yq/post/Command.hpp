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

        CommandInfo(std::string_view zName, PostInfo& base, const std::source_location& sl=std::source_location::current());
    };

    class Command : public Post {
        YQ_OBJECT_INFO(CommandInfo)
        YQ_OBJECT_DECLARE(Command, Post)
        template <class> friend class Ref;
    public:
   
        struct Param : public Post::Param {
        };
        
    protected:
        Command(const Param& p={});
        virtual ~Command();
    };
}
