////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq { 
    template <typename> class Ref;
}

namespace yq::post {
    class Command;
    using CommandPtr    = Ref<Command>;
    using CommandCPtr   = Ref<const Command>;

    class Dispatcher;

    class Event;
    using EventPtr      = Ref<Event>;
    using EventCPtr     = Ref<const Event>;

    class Filter;
    using FilterPtr     = Ref<Filter>;
    using FilterCPtr    = Ref<const Filter>;

    class Message;
    using MessagePtr    = Ref<Message>;
    using MessageCPtr   = Ref<const Message>;

    class Post;
    using PostPtr      = Ref<Post>;
    using PostCPtr     = Ref<const Post>;

    class Request;
    using RequestPtr    = Ref<Request>;
    using RequestCPtr   = Ref<const Request>;

    class Reply;
    using ReplyPtr      = Ref<Reply>;
    using ReplyCPtr     = Ref<const Reply>;

#if 0
    class Filter;
    using FilterPtr     = Ref<Filter>;
    using FilterCPtr    = Ref<const Filter>;
#endif    
}
