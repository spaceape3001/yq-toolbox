////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>
#include <yq/core/Flags.hpp>
#include <yq/post/Post.hpp>
#include <yq/units.hpp>
#include <atomic>
#include <cassert>
#include <cstdint>
#include <functional>
#include <initializer_list>
#include <set>
#include <string_view>
#include <variant>
#include <vector>
#include <tbb/spin_rw_mutex.h>

namespace yq { class Cleanup; }

namespace yq::post {

    /*! \brief Sender/Reciever of posts
    
        The dispatcher is responsible for couriering posts to/from another dispatch.  
        
        A FILTER can be installed, this moderates messages.
        A SNOOP can be installed, this notifies of messages.
        
        \note All sorts of synonyms were mulled through, including Exchange, 
        Office, Box, Courier, etc... Going with dispatcher, for now.  Note, "mailbox" 
        will be *ONE* implementation of a dispatch.
    */
    class Dispatcher {
    public:
    
        //template <typename D>
        //concept Derived = std::derived_from<D,Dispatcher>;
    
        //! Represents a tie between two dispatchers
        class Binding;

        /*! \brief Post FilterFN
        
            This function is a filter, it will return TRUE to accept the message, FALSE to reject.
            First dispatcher is the sender, second is the receiver. 
        */
        //using FilterFN      = std::function<bool(const Dispatcher&, const Dispatcher&, const Post&)>;

        enum class Log : uint8_t {
            Connections,
            Dispatches,
            Receives
        };
        using log_flags_t   = Flags<Log>;


        /*! \brief Post SnoopFN
        
            A snoop is called after filters, but before the event is sent.
        */
        using SnoopFN       = std::function<void(const Dispatcher&, const Dispatcher&, const Post&)>;

        //! Synonyms for senders
        using sender_k      = std::variant<sender_t, from_t, tx_t, pull_t>;
        
        //! Synonyms for recipients
        using receiver_k    = std::variant<recipient_t, receiver_t, to_t, rx_t, push_t>;
        
        using global_k      = std::variant<all_t, global_t>;


        #if 0
        //! Stops the "handle" instead queues up the messages
        void            hold(pull_t);
        
        //! Stops the actual dispatch, queues up messages
        void            hold(push_t);
        #endif

        //! Connects two dispatchers
        static Binding& connect(Dispatcher&from, Dispatcher&to);

        //! Subscribes this message box to receive messages from the sender
        Binding&    connect(sender_k, Dispatcher& sender);

        /*! Subscribes the other message box to our messages
        
            \note Subscribing/unsubscribing is *NOT* currently thread-safe, 
                though dispatching & recieving ought to be.
        
            \param[in] recipient    Dispatcher recipient
            \return Binding reference
        */
        Binding&    connect(receiver_k, Dispatcher& recipient);

        static size_t disconnect(Dispatcher&from, Dispatcher&to);
        static size_t disconnect(Dispatcher&from, Dispatcher&to, std::string_view binding);
        static size_t disconnect(all_t, Dispatcher&to);
        static size_t disconnect(all_t, Dispatcher&to, std::string_view binding);
        static size_t disconnect(Dispatcher&from, all_t);
        static size_t disconnect(Dispatcher&from, all_t, std::string_view binding);

        //! Disconnects ALL in/out named bindings with specified dispatcher
        size_t  disconnect(Dispatcher& other);

        //! Disconnects ALL in/out named bindings with specified dispatcher
        size_t  disconnect(Dispatcher& other, std::string_view);
        
        //! Disconnects ALL in/out
        size_t  disconnect(all_t);

        //! Disconnects ALL in/out with named bindings
        size_t  disconnect(all_t, std::string_view);

        size_t  disconnect(receiver_k, Dispatcher& recipient);
        size_t  disconnect(receiver_k, Dispatcher& recipient, std::string_view);

        size_t  disconnect(receiver_k, all_t);
        size_t  disconnect(receiver_k, all_t, std::string_view);

        //! Disconnects the sender from us
        size_t  disconnect(sender_k, Dispatcher& sender);

        //! Disconnects the sender from us with named binding
        size_t  disconnect(sender_k, Dispatcher& sender, std::string_view binding);

        //! Disconnects ALL senders from us
        size_t  disconnect(sender_k, all_t);

        //! Disconnects ALL senders from us with named binding
        size_t  disconnect(sender_k, all_t, std::string_view binding);

    
        //! This dispatch's name (default will try object-meta)
        virtual std::string_view  name() const;

        //! This dispatch's description (default will try object-meta)
        virtual std::string_view  description() const;

        //! Total number of events generated by this producer
        size_t  dispatched(count_t) const;
        size_t  received(count_t) const;

        //! Total number of connections (in + out)
        size_t  connections(count_t) const;
        
        //! Total number of outbound connections
        size_t  connections(count_t, sender_k) const;
        
        //! Total number of inbound connections
        size_t  connections(count_t, receiver_k) const;

        class Capture;
        
        //! Captures *ALL* messages sent on thread until this object is destroyed
        Capture  capture(thread_t);
        
        //! Captures *ALL* messages sent globally
        //! This is *NOT* thread-safe call, do it at initialization time.  (ie create & set before use)
        //void    capture(global_t);

        #if 0
        //  pending feature idea....
        //! This is *NOT* thread-safe call, do it at initialization time.  (ie create & set before use)
        void            set_cleanup(Cleanup*);
        #endif
        
        #if 0
        //! Installs a global snoop (good for event logging)
        //! This is *NOT* thread-safe call, do it at initialization time.  (ie create & set before use)
        static void install(global_t, SnoopFN&&);
        
        
        void install(SnoopFN&&);
        void install(sender_k, SnoopFN&&);
        void install(receiver_k, SnoopFN&&);
        #endif

        //! Installs a global filter
        //! This is *NOT* thread-safe call, do it at initialization time.  (ie create & set before use)
        static void install(global_t, const FilterCPtr&);

        void install(const FilterCPtr&);
        void install(sender_k, const FilterCPtr&);
        void install(receiver_k, const FilterCPtr&);
        
        struct Param {
            std::string_view    name;
            std::string_view    description;
            log_flags_t         logging = {};
        };
        
        bool    is_listener() const;
        bool    is_poller() const;
        bool    is_global_capture() const;
        
        /*! \brief Polls the dispatcher for posts
        
            This polls the dispatcher for posts.  The timeout, if positive, allows the dispatcher to wait *UP* to the 
            specified duration.
        */
        void    poll(unit::Second timeout=ZERO);
        
        /*! \brief Polls the dispatcher for posts
        
            This polls the dispatcher for posts.  The timeout, if positive, allows the dispatcher to wait *UP* to the 
            specified duration.  The given other dispatcher could be a mailbox, or similar listener, that's used
            temporarily for this polling festival.
        */
        void    poll(Dispatcher&, unit::Second timeout=ZERO);
        
    protected:
        enum class R {
            Listener,       //!< We're a listener to posts
            Poller,         //!< We're a polling source of posts
            GlobalCapture,  //!< Global capture enabled for us
        };
        
        Dispatcher();
        Dispatcher(const Param&p, std::initializer_list<R> classFlags={});
        ~Dispatcher();

        /*! \brief Dispatches a post
        
            \note IF this is the first dispatch for this post, 'const' is ignored
            and the originator/flags are set.
        */
        void            dispatch(const PostCPtr&, Post::flag_initlist_t flags = {});
        
        template <SomePost M>
        const M&        dispatch(const Post* msg, ref_t)
        {
            assert(msg);
            dispatch(msg);
            return *msg;
        }
        
        template <SomePost M>
        const M&        dispatch(const Post* msg, Post::flag_initlist_t flags, ref_t)
        {
            assert(msg);
            dispatch(msg, flags);
            return *msg;
        }

        /*! \brief Your receiver function, extend here
        */
        virtual void    receive(const PostCPtr&){}
        
        /*! \brief Your polling function for messages, extend here
        
            \param[in] timeout (positive & non-zero) gives notional permission to wait up to around 
                the given amount of time
        */
        virtual void    polling(unit::Second) {}
        
        void    description(std::string_view);
        void    name(std::string_view);
        
        void    add_role(R);

    private:
        friend class Post;
        struct Thread;
        struct Postage;
        static Thread&                  thread();
        
        struct Common;
        static Common&                  common();


        Dispatcher(const Dispatcher&) = delete;
        Dispatcher(Dispatcher&&) = delete;
        Dispatcher& operator=(const Dispatcher&) = delete;
        Dispatcher& operator=(Dispatcher&&) = delete;
        
        bool    _accept(Dispatcher& rx, const Post&);
        void    _snoop(Dispatcher& rx, const Post&);
        void    _receive(const PostCPtr&);
        void    _dispatch(const PostCPtr&);
        void    _poll(Dispatcher*, unit::Second);

        using binding_set_t  = std::set<Binding>;
        
        struct Queue {
            std::vector<FilterCPtr>     filters;
            std::vector<SnoopFN>        snoops;
            std::vector<Binding*>       connections;
            std::atomic<size_t>         usage{0};
            //std::vector<PostCPtr>    messages;
            //mutable tbb::spin_rw_mutex  mutex;
            //std::atomic_flag            hold;
        };
        
        Queue                   m_rx, m_tx;
        std::vector<FilterCPtr> m_filters;
        std::vector<SnoopFN>    m_snoops;
        std::string             m_name, m_description;
        std::atomic<int>        m_balance{0};   //< Balance of sent message that still exist
        //Cleanup*            m_cleanup   = nullptr;
        Flags<R>                m_roles;
        log_flags_t             m_logging;
        //! Guard against reentrancy to "polling"
        std::atomic_flag        m_polling;
    };
    
    class Dispatcher::Capture {
    public:
    
        Capture();
        ~Capture();
        
        Capture(Capture&&);
        Capture& operator=(Capture&&);
    
    private:
        friend class Dispatcher;
        Capture(Dispatcher*);
        Dispatcher*      m_box = nullptr;
        
        Capture(const Capture&) = delete;
        Capture& operator=(const Capture&) = delete;
    };

    class Dispatcher::Binding {
    public:
    
        Binding&    operator<<(SnoopFN&&);
        Binding&    operator<<(const FilterCPtr&);
        
        std::string_view name() const { return m_name; }
        Binding&    name(std::string_view);
        
        const Dispatcher& sender() const { return m_sender; }
        const Dispatcher& recipient() const { return m_recipient; }
    
    private:
        friend class Dispatcher;
        
        Binding(Dispatcher& tx, Dispatcher& rx);
        ~Binding();
        
        Dispatcher&             m_sender;
        Dispatcher&             m_recipient;
        std::string             m_name;
        std::vector<FilterCPtr> m_filters;
        std::vector<SnoopFN>    m_snoops;
        
        bool    accept(const Post&) const;
        void    snoop(const Post&) const;
    };
}
