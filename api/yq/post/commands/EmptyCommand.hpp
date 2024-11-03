////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/post/Command.hpp>

namespace yq::post {

    //! Test/general post type that's empty
    class EmptyCommand : public Command {
        YQ_OBJECT_DECLARE(EmptyCommand, Command)
    public:
        
        //  contributing nothing extra....
        using Command::Param;
        
        EmptyCommand(const Param& p = {});
        ~EmptyCommand();
        
        static void init_info();
    };
}
