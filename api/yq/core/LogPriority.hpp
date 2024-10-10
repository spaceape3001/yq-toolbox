////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Enum.hpp>
#include <log4cpp/Priority.hh>

namespace yq {
    //! Basic logging priority
    YQ_ENUM(LogPriority, , 
        //! No logging priority set
        NotSet,
        //! ALL logging levels
        All,
        //!     Debug messages and above
        //! 
        //!     Debug messages tend to be diagnositic and routine in nature, delving into the nitty gritty
        Debug,
        //! Informational messages and above
        //! 
        //! Informational messages are routine in natur
        Info,
        //! Notice messages and above
        //!
        //! Notice will be out-of-ordinary (but not hard to deal with) type of messages
        Notice,
        //! Warning messages and above
        //!
        //! Something is out of place, program can proceed with caution
        Warning,
        
        //! Error messages and above
        //!
        //! Program is unable to do something.  Anticipated/tolerable errors may be here or warnings.
        Error,
        
        //! Something is wrong, heading in the wrong direction, not dire (yet)
        Critical,
        
        //! Likely a coding error, this is more extreme
        Alert,
        
        //! Cannot continue, exiting in a more graceful manner
        Fatal,
        
        //! All hell has broken loose... adios and good luck!
        Emergency
    )

    constexpr int log4cpp_priority(LogPriority p)
    {
        switch(p){
        case LogPriority::NotSet:
        case LogPriority::All:
            return log4cpp::Priority::NOTSET;
        case LogPriority::Debug:
            return log4cpp::Priority::DEBUG;
        case LogPriority::Info:
            return log4cpp::Priority::INFO;
        case LogPriority::Notice:
            return log4cpp::Priority::NOTICE;
        case LogPriority::Warning:
            return log4cpp::Priority::WARN;
        case LogPriority::Error:
            return log4cpp::Priority::ERROR;
        case LogPriority::Critical:
            return log4cpp::Priority::CRIT;
        case LogPriority::Alert:
            return log4cpp::Priority::ALERT;
        case LogPriority::Fatal:
            return log4cpp::Priority::FATAL;
        case LogPriority::Emergency:
        default:
            return log4cpp::Priority::EMERG;
        }
    }
}
