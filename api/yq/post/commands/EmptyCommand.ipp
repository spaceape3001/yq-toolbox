////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "EmptyCommand.hpp"
#include <yq/core/DelayInit.hpp>
#include <yq/post/CommandInfoWriter.hpp>

namespace yq::post {
    EmptyCommand::EmptyCommand(const Param& p) : Command(p) 
    {
    }
    
    EmptyCommand::~EmptyCommand()
    {
    }
    
    static void reg_empty_command()
    {
        auto w = writer<EmptyCommand>();
        w.description("Empty Command");
    }
    
    YQ_INVOKE(
        reg_empty_command();
    );
}

YQ_OBJECT_IMPLEMENT(yq::post::EmptyCommand)
