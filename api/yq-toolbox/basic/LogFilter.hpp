////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/basic/FirstSeen.hpp>
#include <yq-toolbox/basic/Logging.hpp>
#include <yq-toolbox/basic/StringLiteral.hpp>
#include <tuple>
#include <atomic>

namespace yq {
    
    template <StringLiteral, unsigned>
    log4cpp::Priority::Value log_filter_first(log4cpp::Priority::Value def)
    {
        static std::atomic_flag     s_again;
        if(s_again.test_and_set())
            return log4cpp::Priority::NOTSET;
        return def;
    }

    template <StringLiteral, unsigned, typename ... T>
    log4cpp::Priority::Value log_filter_first(log4cpp::Priority::Value def, T ... args)
    {
        using data_t   = std::tuple<T...>;
        static FirstSeen<data_t> s_first;
        if(s_first(data_t(args...))){
            return def;
        }
        return log4cpp::Priority::NOTSET;
    }
}

#define yLogFirstOccurance(pri, cat, ...) ::yq::log_category(cat).getStream(log_filter_first<__FILE__, __LINE__>(pri, __VA_ARGS__))

#define yLogFirstAlert(cat, ...)        yLogFirstOccurance(log4cpp::Priority::ALERT, cat, __VA_ARGS__ )
#define yLogFirstCritical(cat, ...)     yLogFirstOccurance(log4cpp::Priority::CRIT, cat, __VA_ARGS__ )
#define yLogFirstDebug(cat, ...)        yLogFirstOccurance(log4cpp::Priority::DEBUG, cat, __VA_ARGS__ )
#define yLogFirstError(cat, ...)        yLogFirstOccurance(log4cpp::Priority::ERROR, cat, __VA_ARGS__ )
#define yLogFirstEmergency(cat, ...)    yLogFirstOccurance(log4cpp::Priority::EMERG, cat, __VA_ARGS__ )
#define yLogFirstFatal(cat, ...)        yLogFirstOccurance(log4cpp::Priority::FATAL, cat, __VA_ARGS__ )
#define yLogFirstInfo(cat, ...)         yLogFirstOccurance(log4cpp::Priority::INFO, cat, __VA_ARGS__ )
#define yLogFirstNotice(cat, ...)       yLogFirstOccurance(log4cpp::Priority::NOTICE, cat, __VA_ARGS__ )
#define yLogFirstWarning(cat, ...)      yLogFirstOccurance(log4cpp::Priority::WARN, cat, __VA_ARGS__ )

#define yFirstAlert(...)                yLogFirstAlert(nullptr, ...)             
#define yFirstCritical(...)             yLogFirstCritical(nullptr, ...)          
#define yFirstDebug(...)                yLogFirstDebug(nullptr, ...)             
#define yFirstError(...)                yLogFirstError(nullptr, ...)             
#define yFirstEmergency(...)            yLogFirstEmergency(nullptr, ...)         
#define yFirstFatal(...)                yLogFirstFatal(nullptr, ...)             
#define yFirstInfo(...)                 yLogFirstInfo(nullptr, ...)              
#define yFirstNotice(...)               yLogFirstNotice(nullptr, ...)            
#define yFirstWarning(...)              yLogFirstWarning(nullptr, ...)           
