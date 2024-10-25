////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>

#include <yq/post/box/MailBox.hpp>
#include <yq/post/box/PostBox.hpp>
#include <yq/post/box/SimpleBox.hpp>
#include <yq/post/testing/AnyPost.hpp>
#include <yq/post/testing/EmptyPost.hpp>
#include <yq/post/testing/StringPost.hpp>

#include <iostream>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;
using namespace yq::post;

int main()
{
    "Connection"_test = []{

        PostBox     px;
        SimpleBox   sx;
        
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
        PostBox     px;
        SimpleBox   sx;

        px.connect(RX, sx);
        px.send(new EmptyPost);
        
        expect(sx.posts(EMPTY) == false);
        expect(sx.posts(COUNT) == 1);
        
        if(sx.posts(EMPTY))
            return ;
        
        PostCPtr    p   = sx.posts()[0];
        expect(&p->metaInfo() == &meta<EmptyPost>());
    };
    
    return ut::cfg<>.run();
}

