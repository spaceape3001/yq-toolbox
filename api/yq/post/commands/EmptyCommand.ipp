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
    
    void EmptyCommand::init_meta()
    {
        auto w = writer<EmptyCommand>();
        w.description("Empty Command");
    }
}

YQ_OBJECT_IMPLEMENT(yq::post::EmptyCommand)
