////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/meta/MethodInfo.hpp>
#include "MetaWriter.hpp"

namespace yq {

    template <typename R, typename... Args> 
    class MethodInfo::Writer : public Meta::Writer {
    };

    template <> 
    class MethodInfo::Writer<void> : public Meta::Writer {
    public:
        Writer(MethodInfo* m, size_t) : Meta::Writer(m) {}
    };
    
    template <typename R> 
    class MethodInfo::Writer<R> : public Meta::Writer {
    public:
        Meta::Writer    result(std::string_view zName, std::string_view zDescription, options_t opts=0)
        {
            if(Meta::Writer::m_meta)
                static_cast<MethodInfo*>(Meta::Writer::m_meta) -> fill_result_info(zName, zDescription, opts);
            return *this;
        }

        Writer(MethodInfo* m, size_t) : Meta::Writer(m) {}
    };
    
    template <typename T, typename... Args> 
    class MethodInfo::Writer<void,T,Args...> : public Meta::Writer {
    public:
        
        Writer<void, Args...>  argument(std::string_view zName, std::string_view zDescription, options_t opts=0)
        {
            if(Meta::Writer::m_meta)
                static_cast<MethodInfo*>(Meta::Writer::m_meta) -> fill_argument_info(m_arg, zName, zDescription, opts);
            return Writer<void, Args...>( Meta::Writer::m_meta, m_arg + 1);
        }
        
        Writer(MethodInfo* m, size_t n) : Meta::Writer(m), m_arg(n)
        {
        }

    private:
        size_t    m_arg;
    };

    template <typename R, typename T, typename... Args> 
    class MethodInfo::Writer<R,T,Args...> : public Meta::Writer {
    public:
        
        Writer<R, Args...>  argument(std::string_view zName, std::string_view zDescription, options_t opts=0)
        {
            if(Meta::Writer::m_meta)
                static_cast<MethodInfo*>(Meta::Writer::m_meta) -> fill_argument_info(m_arg, zName, zDescription, opts);
            return Writer<R, Args...>( Meta::Writer::m_meta, m_arg + 1);
        }
        
        Writer<void, Args...>    result(std::string_view zName, std::string_view zDescription, options_t opts=0)
        {
            if(Meta::Writer::m_meta)
                static_cast<MethodInfo*>(Meta::Writer::m_meta) -> fill_result_info(zName, zDescription, opts);
            return Writer<void, Args...>( Meta::Writer::m_meta, m_arg );
        }

        Writer(MethodInfo* m, size_t n) : Meta::Writer(m), m_arg(n)
        {
        }

    private:
        size_t    m_arg;
    };
}
