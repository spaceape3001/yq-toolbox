////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    namespace thread {
        //! Gets the current thread's ID
        unsigned int id();
        
        //! Determines the number of processors we're allowed to use, zero if undeterminable
        unsigned int num_processors();
    }

    //! Checks for id being zero
    bool            is_main_thread();
}
