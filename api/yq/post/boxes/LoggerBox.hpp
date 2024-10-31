////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/post/Dispatcher.hpp>
#include <yq/core/Logging.hpp>

namespace yq::post {

    /*! \brief Logs posts to the logger
    
        This logs received posts to the logger using the specified category/priority.
    */
    class LoggerBox : public Dispatcher {
    public:
    
        struct Param {
            const char*     category    = "post";
            LogPriority     priority    = kLogDef_File;
            bool            global      = false;
        };
    
        LoggerBox();
        LoggerBox(const Param&);
        ~LoggerBox();
        
        virtual void    receive(const PostCPtr&) override;

    private:
        log4cpp::Category&  m_category;
        int                 m_priority;
    };
}

