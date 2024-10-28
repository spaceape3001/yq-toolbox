////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////


#include <yq/core/Logging.hpp>
#include <yq/post/triggers/OnCommand.hpp>
#include <yq/post/commands/EmptyCommand.hpp>
#include <yq/post/posts/EmptyPost.hpp>
#include <boost/ut.hpp>

using namespace yq;
using namespace yq::post;

namespace ut = boost::ut;
using namespace ut;

int main(int argc, char* argv[])
{
    log_to_std_output();
    Meta::init();
    Meta::freeze();

    "OnCommand Trigger"_test = []{
        TriggerCPtr trigger = new OnCommand;
        
        PostCPtr        ep  = new EmptyPost;
        PostCPtr        ec  = new EmptyCommand;
        
        expect(ep->metaInfo().is_base(meta<Command>()) == false);
        expect(ep->metaInfo().is_base(meta<Post>())    == true);
        expect(ec->metaInfo().is_base(meta<Command>()) == true);
        expect(ec->metaInfo().is_base(meta<Post>())    == true);
        
        expect(trigger->passed(*ep) == false);
        expect(trigger->passed(*ec) == true);
        
    };

    return ut::cfg<>.run();
}

