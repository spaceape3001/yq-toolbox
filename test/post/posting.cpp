////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>

#include <yq/core/Logging.hpp>
#include <yq/meta/Meta.hpp>

#include <yq/post/boxes/MailBox.hpp>
#include <yq/post/boxes/PostBox.hpp>
#include <yq/post/boxes/SimpleBox.hpp>
#include <yq/post/posts/AnyPost.hpp>
#include <yq/post/posts/EmptyPost.hpp>
#include <yq/post/posts/StringPost.hpp>

#include <iostream>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;
using namespace yq::post;

int main()
{
    log_to_std_output();
    Meta::freeze();

    "Connection"_test = []{
        PostBox     px;
        SimpleBox   sx({
            .logging    = ALL
        });
        
        px.connect(RX, sx);
        
        expect(sx.connections(COUNT) == 1);
        expect(sx.connections(COUNT, RX) == 1);
        expect(sx.connections(COUNT, TX) == 0);

        expect(px.connections(COUNT) == 1);
        expect(px.connections(COUNT, RX) == 0);
        expect(px.connections(COUNT, TX) == 1);
        
        px.disconnect(ALL);

        expect(sx.connections(COUNT) == 0);
        expect(sx.connections(COUNT, RX) == 0);
        expect(sx.connections(COUNT, TX) == 0);

        expect(px.connections(COUNT) == 0);
        expect(px.connections(COUNT, RX) == 0);
        expect(px.connections(COUNT, TX) == 0);
    };
    
    "EmptyPost"_test = []{
        PostBox     px({
            .logging    = ALL
        });
        SimpleBox   sx({
            .logging    = ALL
        });

        px.connect(RX, sx);
        px.send(new EmptyPost);
        
        expect(sx.posts(EMPTY) == false);
        expect(sx.posts(COUNT) == 1);
        
        if(sx.posts(EMPTY))
            return ;
        
        PostCPtr    p   = sx.posts()[0];
        expect(&p->metaInfo() == &meta<EmptyPost>());
    };
    
    "StringPost"_test = []{
        MailBox     mx;
        PostBox     px;
        
        const char* msg = "There once was an old hag whose house was a boot.";
        
        px.connect(RX, mx);
        px.send(new StringPost(msg));
        
        std::vector<PostCPtr>   posts   = mx.posts(PICKUP);
        expect(posts.size() == 1);
        
        if(posts.empty())
            return ;
            
        PostCPtr        p   = posts[0];
        expect(&p->metaInfo() == &meta<StringPost>());
        const StringPost    *sp = static_cast<const StringPost*>(p.ptr());
        expect( sp->text() == msg);
    };
    
    
    return ut::cfg<>.run();
}

