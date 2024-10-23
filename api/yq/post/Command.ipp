////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Command.hpp"
#include "CommandInfoWriter.hpp"
#include <yq/core/DelayInit.hpp>

YQ_OBJECT_IMPLEMENT(yq::post::Command)

namespace yq::post {
    CommandInfo::CommandInfo(std::string_view zName, const PostInfo& base, const std::source_location& sl) :
        PostInfo(zName, base, sl)
    {
        set(Flag::COMMAND);
    }

    ////////////////////////////////////////////////////////////////////////////

    Command::Command(const Param& p) : Post(p)
    {
    }
    
    Command::~Command()
    {
    }


    ////////////////////////////////////////////////////////////////////////////

    static void reg_command()
    {
        auto w = writer<Command>();
        w.description("Abstract Command Class");
    }
    
    YQ_INVOKE(reg_command();)
}
