////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <vector>
#include <chrono>

namespace yq {

    class ByteArray;

        /*! \brief Structure for executeProcessSeries
        
            This captures the arguments that would be passed to executeProcess, 
            if the processes were called individually.
        */
    struct ProcessDescriptor {

        /*! \brief Command line arguments (item[0] is the command)
        */
        std::vector<std::string> args;
        
        /*! \brief Maximum wait time for exit
        
            Rather than hanging the caller, this specifies the maximum wait
            time before considering the process "hung".  Note, specifying "0"
            will block forever until the program completes.
        */
        int         wait = 500;
        
        ByteArray       execute(const ByteArray& stdInput, ByteArray* stdErrors=nullptr, int *exit_code=nullptr) const;
    };


}


