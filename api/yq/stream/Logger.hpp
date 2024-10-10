////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Stream.hpp>
#include <log4cpp/CategoryStream.hh>

namespace yq::stream {

    class Logger : public Stream {
    public:
        Logger(log4cpp::CategoryStream);
        ~Logger();
        
        //! Overload that appends to the string
        bool write(const char* buf, size_t cb) override;
        void    close() override;
        
    private:
        log4cpp::CategoryStream     m_log;
    };
}
