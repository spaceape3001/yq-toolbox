////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/MethodMeta.hpp>
#include "MetaWriter.hpp"

namespace yq {

    template <typename R, typename... Args> 
    class MethodMeta::Writer : public Meta::Writer {
    };

    template <> 
    class MethodMeta::Writer<void> : public Meta::Writer {
    public:
        Writer(MethodMeta* m, size_t) : Meta::Writer(m) {}
        Writer() : Meta::Writer(nullptr) {}
    };
    
    template <typename R> 
    class MethodMeta::Writer<R> : public Meta::Writer {
    public:
        Meta::Writer    result(std::string_view zName, std::string_view zDescription=std::string_view())
        {
            if(Meta::Writer::m_meta)
                static_cast<MethodMeta*>(Meta::Writer::m_meta) -> fill_result_info(zName, zDescription);
            return *this;
        }

        Writer(MethodMeta* m, size_t) : Meta::Writer(m) {}
        Writer() : Meta::Writer(nullptr) {}
    };
    
    template <typename T, typename... Args> 
    class MethodMeta::Writer<void,T,Args...> : public Meta::Writer {
    public:
        
        Writer<void, Args...>  argument(std::string_view zName, std::string_view zDescription=std::string_view())
        {
            if(Meta::Writer::m_meta)
                static_cast<MethodMeta*>(Meta::Writer::m_meta) -> fill_argument_info(m_arg, zName, zDescription);
            return Writer<void, Args...>( static_cast<MethodMeta*>(Meta::Writer::m_meta), m_arg + 1);
        }
        
        Writer(MethodMeta* m, size_t n) : Meta::Writer(m), m_arg(n)
        {
        }
        
        Writer() : Meta::Writer(nullptr), m_arg(~0ULL)
        {
        }

    private:
        size_t    m_arg;
    };

    template <typename R, typename T, typename... Args> 
    class MethodMeta::Writer<R,T,Args...> : public Meta::Writer {
    public:
        
        Writer<R, Args...>  argument(std::string_view zName, std::string_view zDescription=std::string_view())
        {
            if(Meta::Writer::m_meta)
                static_cast<MethodMeta*>(Meta::Writer::m_meta) -> fill_argument_info(m_arg, zName, zDescription);
            return Writer<R, Args...>( static_cast<MethodMeta*>(Meta::Writer::m_meta), m_arg + 1);
        }
        
        Writer<void, Args...>    result(std::string_view zName, std::string_view zDescription=std::string_view())
        {
            if(Meta::Writer::m_meta)
                static_cast<MethodMeta*>(Meta::Writer::m_meta) -> fill_result_info(zName, zDescription);
            return Writer<void, Args...>( static_cast<MethodMeta*>(Meta::Writer::m_meta), m_arg );
        }

        Writer(MethodMeta* m, size_t n) : Meta::Writer(m), m_arg(n)
        {
        }

        Writer() : Meta::Writer(nullptr), m_arg(~0ULL)
        {
        }

    private:
        size_t    m_arg;
    };
}
