////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Command.hpp"
#include "CommandInfoWriter.hpp"

YQ_OBJECT_IMPLEMENT(yq::post::Command)

namespace yq::post {
    CommandInfo::CommandInfo(std::string_view zName, PostInfo& base, const std::source_location& sl) :
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

    void Command::init_info()
    {
        auto w = writer<Command>();
        w.description("Abstract Command Class");
    }
}
