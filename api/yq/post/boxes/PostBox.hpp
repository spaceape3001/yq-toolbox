////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/post/Dispatcher.hpp>

namespace yq::post {

    /*! \brief Post mailer
    
        This is a drop-box for posting things, it will not recieve.  
        (See mail/simple box for receiving)
    */
    class PostBox : public Dispatcher {
    public:
        using Param = Dispatcher::Param;
    
        PostBox(const Param& p = Param());
        ~PostBox();
        
        void    send(const PostCPtr&);

    protected:
        std::vector<PostCPtr>   m_posts;
    };

}
