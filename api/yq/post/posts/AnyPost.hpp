////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Any.hpp>
#include <yq/post/Post.hpp>

namespace yq::post {

    /*! \brief Test post, carries an any value
    */
    class AnyPost : public Post {
        YQ_OBJECT_DECLARE(AnyPost, Post)
    public:
    
        using Post::Param;
        
        AnyPost(const Any& val, const Param&p={});
        AnyPost(Any&& val, const Param&p={});
        ~AnyPost();
    
        const Any&    value() const { return m_value; }
        
        static void init_info();
    
    private:
        Any     m_value;
    };
}
