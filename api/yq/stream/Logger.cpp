////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Logger.hpp"
#include <yq/core/StreamOps.hpp>

namespace yq::stream {
    Logger::Logger(log4cpp::CategoryStream cstr) : m_log(cstr)
    {
    }
    
    Logger::~Logger()
    {
    }

    void Logger::close() 
    {
        m_log.flush();
    }
    
    bool Logger::write(const char* buf, size_t cb) 
    {
        if(buf && cb){
            m_log << std::string_view(buf, cb);
        }
        return true;
    }
}
