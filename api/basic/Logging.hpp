////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/DbgRel.hpp>
#include <basic/Enum.hpp>
#include <basic/Flag.hpp>
#include <log4cpp/Category.hh>
#include <log4cpp/CategoryStream.hh>
#include <log4cpp/Priority.hh>
#include <optional>


namespace yq {

    YQ_ENUM(LogPriority, , 
        NotSet,
        All,
        Debug,
        Info,
        Notice,
        Warning,
        Error,
        Critical,
        Alert,
        Fatal,
        Emergency
    )


    class String;

    // suggestions (not required)
    static constexpr const auto  kLogDef_Console = YQ_DBGREL(LogPriority::Debug, LogPriority::Warning);
    static constexpr const auto  kLogDef_File    = YQ_DBGREL(LogPriority::Debug, LogPriority::Info);


    template <typename E>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&str, EnumImpl<E> v)
    {
        return str << v.key();
    }

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

    log4cpp::Category&          log_category(const char* z=nullptr);

    //int							yLogPriority(LogPriority);

    void                        log_to_std_error(LogPriority p = LogPriority());
    void                        log_to_std_output(LogPriority p = LogPriority());
    void                        log_to_file(const std::filesystem::path&, LogPriority p = LogPriority());

    //void                        log_freeze();

    LogPriority                 log_std_output_priority();
    LogPriority                 log_std_error_priority();
    bool                        is_log_std_output_enabled();
    bool                        is_log_std_error_enabled();


    #define yAlert(...)         ::yq::log_category(__VA_ARGS__).alertStream()
    #define yCritical(...)      ::yq::log_category(__VA_ARGS__).critStream()
    #define yDebug(...)         ::yq::log_category(__VA_ARGS__).debugStream()
    #define yError(...)         ::yq::log_category(__VA_ARGS__).errorStream()
    #define yEmergency(...)     ::yq::log_category(__VA_ARGS__).emergStream()
    #define yFatal(...)         ::yq::log_category(__VA_ARGS__).fatalStream()
    #define yInfo(...)          ::yq::log_category(__VA_ARGS__).infoStream()
    #define yNotice(...)        ::yq::log_category(__VA_ARGS__).noticeStream()
    #define yWarning(...)       ::yq::log_category(__VA_ARGS__).warnStream()

}

template <typename T>
log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& str, const std::optional<T>&v)
{
    if(v)
        str << *v;
    else
        str << "(unset)";
    return str;
}

//log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const QByteArray&);
//log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const QDate&);
//log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const QDateTime&);
//log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const QDir&);
//log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const QSqlError&);
//log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const QString&);
//log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const QUrl&);
