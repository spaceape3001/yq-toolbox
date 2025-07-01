////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>

#include <yq/core/Logging.hpp>
#include <yq/meta/Meta.hpp>
#include <yq/post/Command.hpp>
#include <yq/post/PBX.hpp>
#include <yq/post/PBXInfoWriter.hpp>
#include <yq/post/boxes/PostBox.hpp>
#include <yq/post/commands/EmptyCommand.hpp>
#include <yq/post/posts/EmptyPost.hpp>
#include <yq/post/triggers/OnCommand.hpp>

using namespace yq;
using namespace yq::post;

class SampleCommand : public Command {
    YQ_OBJECT_DECLARE(SampleCommand, Command)
public:

    static void init_meta()
    {
    }
};

YQ_OBJECT_IMPLEMENT(SampleCommand)
//YQ_OBJECT_IMPLEMENT(OnCommand)

class TestPBX1 : public PBX {
    YQ_OBJECT_DECLARE(TestPBX1, PBX)
public:

    size_t  m_command1  = 0;

    void    command1()
    {
        ++ m_command1;
    }

    static void init_meta()
    {
        auto w = writer<TestPBX1>();
        w.receive(&TestPBX1::command1, new OnCommand);
    }
};

YQ_OBJECT_IMPLEMENT(TestPBX1)


namespace ut = boost::ut;
using namespace ut;

int main(int argc, char* argv[])
{
    log_to_std_output();
    Meta::init();
    TestPBX1::init_meta();
    SampleCommand::init_meta();
    Meta::freeze();

    "Command1"_test = []{
        PostBox     tx;
        TestPBX1    pbx;
        pbx.connect(TX, tx);
        
        expect(pbx.m_command1 == 0);
        tx.send(new EmptyPost);
        expect(pbx.m_command1 == 0);
        tx.send(new EmptyCommand);
        expect(pbx.m_command1 == 1);
        tx.send(new SampleCommand);
        expect(pbx.m_command1 == 2);
    };

    return ut::cfg<>.run();
}

