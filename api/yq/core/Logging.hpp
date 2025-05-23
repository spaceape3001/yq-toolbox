////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/LogPriority.hpp>
#include <yq/core/Flag.hpp>
#include <yq/macro/debugrel.hpp>
#include <yq/typedef/filesystem_path.hpp>
#include <log4cpp/Category.hh>
#include <log4cpp/CategoryStream.hh>
#include <log4cpp/Priority.hh>
#include <optional>
#include <source_location>
#include <string_view>
#include <system_error>

namespace yq {

    //class String;

    // suggestions (not required)
    //! Suggested console logging
    static constexpr const auto  kLogDef_Console = YQ_DBGREL(LogPriority::Debug, LogPriority::Warning);
    //! Suggested file logging
    static constexpr const auto  kLogDef_File    = YQ_DBGREL(LogPriority::Debug, LogPriority::Info);


    //! Stream an enumeration to the logger
    template <typename E>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&str, EnumImpl<E> v)
    {
        return str << v.key();
    }

    //! Stream an enumeration flag set to the logger
    template <typename E>
    log4cpp::CategoryStream&     operator<<(log4cpp::CategoryStream& str, Flag<E> val)
    {
        str << '{';
        bool f = true;
        for(E e : E::all_values()){
            if(val.is_set(e)){
                if(f){
                    f   = false;
                } else 
                    str << "|";
                str << e.key();
            }
        }
        str << '}';
        return str;
    }

    //! Get a new logger based on category
    log4cpp::Category&          log_category(const char* z=nullptr);

    //int							yLogPriority(LogPriority);

    //! Enable logging to standard error
    //! \param[in] p    Minimum logging threshhold to actually report
    void                        log_to_std_error(LogPriority p = LogPriority());
    //! Enable logging to standard output
    //! \param[in] p    Minimum logging threshhold to actually report
    void                        log_to_std_output(LogPriority p = LogPriority());
    //! Enable logging to a file
    //! \param[in] fp   Filepath to log to
    //! \param[in] p    Minimum logging threshhold to actually report
    void                        log_to_file(const filesystem_path_t& fp, LogPriority p = LogPriority());

    //void                        log_freeze();

    //! Returns the current standard output logging priority
    LogPriority                 log_std_output_priority();
    //! Returns the current standard error logging priority
    LogPriority                 log_std_error_priority();
    //! TRUE if we're logging to standard output
    bool                        is_log_std_output_enabled();
    //! TRUE if we're logging to standard error
    bool                        is_log_std_error_enabled();

    //! Macro to get an alert-level log stream
    #define yAlert(...)         ::yq::log_category(__VA_ARGS__).alertStream()
    //! Macro to get a critical-level log stream
    #define yCritical(...)      ::yq::log_category(__VA_ARGS__).critStream()
    //! Macro to get a debug-level log stream
    #define yDebug(...)         ::yq::log_category(__VA_ARGS__).debugStream()
    //! Macro to get an error-level log stream
    #define yError(...)         ::yq::log_category(__VA_ARGS__).errorStream()
    //! Macro to get an emergency-level log stream
    #define yEmergency(...)     ::yq::log_category(__VA_ARGS__).emergStream()
    //! Macro to get a fatal-level log stream
    #define yFatal(...)         ::yq::log_category(__VA_ARGS__).fatalStream()
    //! Macro to get an informational-level log stream
    #define yInfo(...)          ::yq::log_category(__VA_ARGS__).infoStream()
    //! Macro to get a notice-level log stream
    #define yNotice(...)        ::yq::log_category(__VA_ARGS__).noticeStream()
    //! Macro to get a warning-level log stream
    #define yWarning(...)       ::yq::log_category(__VA_ARGS__).warnStream()

}

//! Used to log an optional item, by logging either the value or (unset)
template <typename T>
log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& str, const std::optional<T>&v)
{
    if(v)
        str << *v;
    else
        str << "(unset)";
    return str;
}

log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const std::error_code&);
log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, std::u32string_view);
log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const std::u32string&);

//log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const QByteArray&);
//log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const QDate&);
//log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const QDateTime&);
//log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const QDir&);
//log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const QSqlError&);
//log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const QString&);
//log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const QUrl&);
