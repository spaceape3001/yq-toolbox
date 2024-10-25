////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/post/Post.hpp>
#include <string>
#include <string_view>

namespace yq::post {

    //! Test post type that carries a string 
    class StringPost : public Post {
        YQ_OBJECT_DECLARE(StringPost, Post)
    public:
    
        using text_t    = std::variant<std::monostate, const char*, std::string_view, std::string>;
        
        using Post::Param;
        
        StringPost(std::string&&, const Param& p = {});
        StringPost(const char*, const Param& p = {});
        StringPost(std::string_view, const Param& p = {});
        ~StringPost(){}
    
        const std::string&    text() const { return m_text; }
    
    private:
        std::string     m_text;
    };
}
