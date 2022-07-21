////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Logging.hpp"

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
        
        int							log_priority(LogPriority p)
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
        return _r.m_err ? true : false;
    }

    bool                        is_log_std_output_enabled()
    {
        LOCK
        return _r.m_out ? true : false;
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
            _r.m_err -> setThreshold(log_priority(lp));
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
            _r.m_out -> setThreshold(log_priority(lp));
        }
    }

    void                        log_to_file(const std::filesystem::path&file, LogPriority p)
    {
        log4cpp::FileAppender* f    = new log4cpp::FileAppender(file.string(), file.string());
        if(p != LogPriority())
            f -> setThreshold(log_priority(p));
        WLOCK
        _r.m_root.addAppender(f);
    }

}

