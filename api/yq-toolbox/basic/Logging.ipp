////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Logging.hpp"

#include <yq-toolbox/text/format.hpp>

#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>

    // hack because Qt #define emit for their MOC and tbb now uses it.
#ifdef emit
#undef emit
#endif
#include <tbb/spin_mutex.h>
#include <tbb/spin_rw_mutex.h>

//#include <QByteArray>
//#include <QDate>
//#include <QDateTime>
//#include <QDir>
//#include <QSqlError>
//#include <QUrl>

#include <iostream>

namespace yq {

    namespace {

        struct LogRepo {
            log4cpp::Category&                                  m_root;
            tbb::spin_rw_mutex                                  m_mutex;
            log4cpp::OstreamAppender*                           m_out;
            LogPriority                                         m_outPri;
            log4cpp::OstreamAppender*                           m_err;
            LogPriority                                         m_errPri;
            
            LogRepo() :    m_root(log4cpp::Category::getRoot()), 
                        m_out(nullptr), 
                        m_err(nullptr)
            {
                //root.removeAllAppenders();
                log4cpp::Category::setRootPriority(log4cpp::Priority::DEBUG);
            }
            
            log4cpp::Category*  make(const char* z)
            {
                if(!z || !*z)
                    return &m_root;
                return &log4cpp::Category::getInstance(z);
            }
        };
        
        
        #define LOCK    \
            LogRepo& _r = log_repo(); \
            tbb::spin_rw_mutex::scoped_lock _lock(_r.m_mutex, false); 

        #define WLOCK    \
            LogRepo& _r = log_repo(); \
            tbb::spin_rw_mutex::scoped_lock _lock(_r.m_mutex, false); 
        
        
        LogRepo& log_repo()
        {
            static LogRepo s_repo;
            return s_repo;
        }
    }

    bool                        is_log_std_error_enabled()
    {
        LOCK
        return static_cast<bool>(_r.m_err);
    }

    bool                        is_log_std_output_enabled()
    {
        LOCK
        return static_cast<bool>(_r.m_out);
    }

    log4cpp::Category&          log_category(const char* z)
    {
        auto& _r = log_repo();
        if(!z || !*z)
            return _r.m_root;
        else
            return log4cpp::Category::getInstance(z);
    }

    LogPriority                 log_std_error_priority()
    {
        LOCK
        return _r.m_errPri;
    }


    LogPriority                 log_std_output_priority()
    {
        LOCK
        return _r.m_outPri;
    }


    void                        log_to_std_error(LogPriority lp)
    {
        WLOCK
        if(!_r.m_err){
            _r.m_err    = new log4cpp::OstreamAppender(std::string(), &std::cerr);
            _r.m_root.addAppender(_r.m_err);
        }
        if(lp != LogPriority()){
            _r.m_errPri = lp;
            _r.m_err -> setThreshold(log4cpp_priority(lp));
        }
    }


    void                        log_to_std_output( LogPriority lp)
    {
        WLOCK
        if(!_r.m_out){
            _r.m_out    = new log4cpp::OstreamAppender(std::string(), &std::cout);
            _r.m_root.addAppender(_r.m_out);
        }
        if(lp != LogPriority()){
            _r.m_outPri = lp;
            _r.m_out -> setThreshold(log4cpp_priority(lp));
        }
    }

    void                        log_to_file(const filesystem_path_t&file, LogPriority p)
    {
        log4cpp::FileAppender* f    = new log4cpp::FileAppender(file.string(), file.string());
        if(p != LogPriority())
            f -> setThreshold(log4cpp_priority(p));
        WLOCK
        _r.m_root.addAppender(f);
    }

}

log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&str, const std::error_code&ec)
{
    str << ec.message();
    return str;
}

log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& out, std::u32string_view sv)
{
    for(char32_t ch : sv)
        out << yq::to_string_view(ch);
    return out;
}

log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&out, const std::u32string&s)
{
    return out << (std::u32string_view) s;
}



