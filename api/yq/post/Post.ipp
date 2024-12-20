////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Post.hpp"
#include "PostInfoWriter.hpp"
#include <yq/core/ThreadId.hpp>
#include <yq/post/Dispatcher.hpp>

YQ_OBJECT_IMPLEMENT(yq::post::Post)

namespace yq::post {
    PostInfo::PostInfo(std::string_view zName, ObjectInfo& base, const std::source_location& sl) :
        ObjectInfo(zName, base, sl)
    {
        set(Flag::POST);
    }

    ////////////////////////////////////////////////////////////////////////////

    std::atomic<uint64_t>    Post::s_lastId{0};

    Post::Post(const Param& p) : 
        m_id(++s_lastId), 
        m_time(clock_t::now()), 
        m_thread(thread::id()),
        m_flags(p.flags)
    {
    }
    
    Post::~Post()
    {
        if(m_originator){
            --(m_originator -> m_balance);
        }
    }

    bool Post::handled() const
    {
        return m_handled.test();
    }

    bool Post::mark() const
    {
        return !m_handled.test_and_set();
    }

    void Post::reset() const
    {
        m_handled.clear();
    }

    bool Post::has(flag_t f) const
    {
        return m_flags[f];
    }

    bool Post::has(any_t, std::initializer_list<flag_t> flags) const
    {
        for(flag_t f : flags){
            if(m_flags[f])
                return true;
        }
        return false;
    }
    
    bool Post::has(all_t, std::initializer_list<flag_t> flags) const
    {
        for(flag_t f : flags){
            if(!m_flags[f])
                return false;
        }
        return true;
    }

    ////////////////////////////////////////////////////////////////////////////

    void Post::init_info()
    {
        auto w = writer<Post>();
        w.description("Abstract Post Base Class");
        w.property("handled", &Post::handled).description("TRUE if the message has been dealt with");
        w.property("id", &Post::id).description("Post ID (do NOT assume monoticity)");
    }
}
