////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>
#include <yq/core/Flags.hpp>
#include <yq/core/Object.hpp>
#include <yq/core/Ref.hpp>
#include <yq/typedef/post.hpp>
#include <atomic>
#include <chrono>
#include <concepts>

namespace yq::post {
    class Mailer;
    
    class PostInfo : public ObjectInfo {
    public:
        template <typename C> class Writer;

        PostInfo(std::string_view zName, const ObjectInfo& base, const std::source_location& sl=std::source_location::current());
    };
    
    /*! \brief Light weight message, which can be an event, an input, a command, a request, etc.
    
        The post is supposed to be light weight, used to courier to another 
        listener via the mailer.
    */
    class Post : public Object, public RefCount {
        YQ_OBJECT_INFO(PostInfo)
        YQ_OBJECT_DECLARE(Post, Object)
    public:
    
        //! allow for message flags... not yet determined
        using flag_t        = uint16_t;
        
        //! all flags 
        using flags_t       = BitArray<uint64_t,4>;
    
    
        /*! \brief Parameter structure
        
            All data parameters needed for the message... derived classes 
            derive from this.  These structures should generally all be publicly
            accessible data with reasonably defaulted parameters.
        */
        struct Param {
            flags_t         flags;
        };
    
    
        using time_point_t  = std::chrono::high_resolution_clock::time_point;
    
        virtual ~Post();
        
        // Invalid reference until published
        Mailer&                originator() const { return *m_originator; }
        
        //! TRUE if somebody's "dealt" with the message
        bool                handled() const;
        
        //! TRUE if this has been published
        bool                published() const { return static_cast<bool>(m_originator); }
        
        //! Marks the message as handled (unconditional)
        bool                mark() const;
        
        //! Resets the message handled flag
        void                reset() const;
        
        //! Time of message creation
        const time_point_t& time() const { return m_time; }
        
        //! Post identifier (executable-unique)
        uint64_t            id() const { return m_id; }
        
        bool                has(flag_t f) const;
        
        //! Detects for all flags being set
        //! \note an empty list will return TRUE
        bool                has(all_t, std::initializer_list<flag_t>) const;

        //! Detects for any flag being set
        //! \note an empty list will return FALSE
        bool                has(any_t, std::initializer_list<flag_t>) const;
        
    protected:

        Post(const Param&);
        
    private:
        friend class Mailer;
        
        const uint64_t              m_id;
        const time_point_t          m_time;
        flags_t                     m_flags;
        Mailer*                        m_originator    = nullptr;
        mutable std::atomic_flag    m_handled;
        
        Post(const Post&) = delete;
        Post(Post&&) = delete;
        Post& operator=(const Post&) = delete;
        Post& operator=(Post&&) = delete;
        
        static std::atomic<uint64_t>    s_lastId;
    };
    
    template <typename E>
    concept SomePost = std::derived_from<E, Post>;
}
