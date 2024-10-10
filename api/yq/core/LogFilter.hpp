////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/FirstSeen.hpp>
#include <yq/core/Logging.hpp>
#include <yq/core/StringLiteral.hpp>
#include <tuple>
#include <atomic>

namespace yq {
    
    template <StringLiteral, unsigned>
    log4cpp::Priority::Value log_once(log4cpp::Priority::Value def)
    {
        static std::atomic_flag     s_again;
        if(s_again.test_and_set())
            return log4cpp::Priority::NOTSET;
        return def;
    }

    template <StringLiteral, unsigned, typename ... T>
    log4cpp::Priority::Value log_first(log4cpp::Priority::Value def, T ... args)
    {
        using data_t   = std::tuple<T...>;
        static FirstSeen<data_t> s_first;
        if(s_first(data_t(args...))){
            return def;
        }
        return log4cpp::Priority::NOTSET;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Log once and only once (per invocation)
#define yLogOnce(pri, cat)              ::yq::log_category(cat).getStream(log_once<__FILE__, __LINE__>(pri))

#define yLogOnceAlert(cat)              yLogOnce(log4cpp::Priority::ALERT, cat)
#define yLogOnceCritical(cat)           yLogOnce(log4cpp::Priority::CRIT, cat)
#define yLogOnceDebug(cat)              yLogOnce(log4cpp::Priority::DEBUG, cat)
#define yLogOnceError(cat)              yLogOnce(log4cpp::Priority::ERROR, cat)
#define yLogOnceEmergency(cat)          yLogOnce(log4cpp::Priority::EMERG, cat)
#define yLogOnceFatal(cat)              yLogOnce(log4cpp::Priority::FATAL, cat)
#define yLogOnceInfo(cat)               yLogOnce(log4cpp::Priority::INFO, cat)
#define yLogOnceNotice(cat)             yLogOnce(log4cpp::Priority::NOTICE, cat)
#define yLogOnceWarning(cat)            yLogOnce(log4cpp::Priority::WARN, cat)

#define yOnceAlert                      yLogOnceAlert(nullptr)             
#define yOnceCritical                   yLogOnceCritical(nullptr)          
#define yOnceDebug                      yLogOnceDebug(nullptr)             
#define yOnceError                      yLogOnceError(nullptr)             
#define yOnceEmergency                  yLogOnceEmergency(nullptr)         
#define yOnceFatal                      yLogOnceFatal(nullptr)             
#define yOnceInfo                       yLogOnceInfo(nullptr)              
#define yOnceNotice                     yLogOnceNotice(nullptr)            
#define yOnceWarning                    yLogOnceWarning(nullptr)           


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Log the first time based on filter
#define yLogFirst(pri, cat, ...)    ::yq::log_category(cat).getStream(log_first<__FILE__, __LINE__>(pri, __VA_ARGS__))

#define yLogFirstAlert(cat, ...)        yLogFirst(log4cpp::Priority::ALERT, cat, __VA_ARGS__ )
#define yLogFirstCritical(cat, ...)     yLogFirst(log4cpp::Priority::CRIT, cat, __VA_ARGS__ )
#define yLogFirstDebug(cat, ...)        yLogFirst(log4cpp::Priority::DEBUG, cat, __VA_ARGS__ )
#define yLogFirstError(cat, ...)        yLogFirst(log4cpp::Priority::ERROR, cat, __VA_ARGS__ )
#define yLogFirstEmergency(cat, ...)    yLogFirst(log4cpp::Priority::EMERG, cat, __VA_ARGS__ )
#define yLogFirstFatal(cat, ...)        yLogFirst(log4cpp::Priority::FATAL, cat, __VA_ARGS__ )
#define yLogFirstInfo(cat, ...)         yLogFirst(log4cpp::Priority::INFO, cat, __VA_ARGS__ )
#define yLogFirstNotice(cat, ...)       yLogFirst(log4cpp::Priority::NOTICE, cat, __VA_ARGS__ )
#define yLogFirstWarning(cat, ...)      yLogFirst(log4cpp::Priority::WARN, cat, __VA_ARGS__ )

#define yFirstAlert(...)                yLogFirstAlert(nullptr, ...)             
#define yFirstCritical(...)             yLogFirstCritical(nullptr, ...)          
#define yFirstDebug(...)                yLogFirstDebug(nullptr, ...)             
#define yFirstError(...)                yLogFirstError(nullptr, ...)             
#define yFirstEmergency(...)            yLogFirstEmergency(nullptr, ...)         
#define yFirstFatal(...)                yLogFirstFatal(nullptr, ...)             
#define yFirstInfo(...)                 yLogFirstInfo(nullptr, ...)              
#define yFirstNotice(...)               yLogFirstNotice(nullptr, ...)            
#define yFirstWarning(...)              yLogFirstWarning(nullptr, ...)           

