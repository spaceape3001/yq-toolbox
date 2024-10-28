////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <concepts>
#include <yq/core/Flags.hpp>

namespace yq { 
    template <typename> class Ref;
}

namespace yq::post {
    class Command;
    using CommandPtr        = Ref<Command>;
    using CommandCPtr       = Ref<const Command>;

    class Dispatcher;

    class Event;
    using EventPtr          = Ref<Event>;
    using EventCPtr         = Ref<const Event>;

    class Filter;
    using FilterPtr         = Ref<Filter>;
    using FilterCPtr        = Ref<const Filter>;

    class Message;
    using MessagePtr        = Ref<Message>;
    using MessageCPtr       = Ref<const Message>;

    class PBX;
    class PBXDispatch;
    class PBXInfo;

    class Post;
    class PostInfo;
    using PostPtr           = Ref<Post>;
    using PostCPtr          = Ref<const Post>;
    
    class Request;
    using RequestPtr        = Ref<Request>;
    using RequestCPtr       = Ref<const Request>;

    class Reply;
    using ReplyPtr          = Ref<Reply>;
    using ReplyCPtr         = Ref<const Reply>;

    class Trigger;
    using TriggerPtr        = Ref<Trigger>;
    using TriggerCPtr       = Ref<const Trigger>;

    template <class C>
    concept SomeCommand     = std::derived_from<C,Command>;
    
    template <class D>
    concept SomeDispatcher  = std::derived_from<D,Dispatcher>;
    
    template <class E>
    concept SomeEvent       = std::derived_from<E,Event>;

    template <class F>
    concept SomeFilter      = std::derived_from<F,Filter>;
    
    template <class M>
    concept SomeMessage     = std::derived_from<M,Message>;
    
    template <class P>
    concept SomePBX         = std::derived_from<P,PBX>;
    
    template <class P>
    concept SomePost        = std::derived_from<P,Post>;
    
    template <class R>
    concept SomeReply       = std::derived_from<R,Reply>;
    
    template <class R>
    concept SomeRequest     = std::derived_from<R,Request>;
    
    template <class T>
    concept SomeTrigger     = std::derived_from<T,Trigger>;

    //! Filter Mismatch
    //!
    //! When calling a filter, the parameters might mismatch
    //! and this enum/flag pair captures that
    enum class MismatchType : uint8_t {
        InSender,
        InReceiver,
        InPost
    };
    
    using MismatchFlags     = Flags<MismatchType, uint8_t>;

    
    //! Used by trigger when there's one
    enum class MismatchPolicy : uint8_t {
        Reject  = 0,
        Accept
    };

    
    
}
