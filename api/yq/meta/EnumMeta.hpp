////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/errors.hpp>
#include <yq/core/Enumeration.hpp>
#include <yq/meta/TypeMetaWriter.hpp>
#include <yq/typedef/expected.hpp>

namespace yq {
    template <typename E>
    requires std::is_enum_v<E>
    class TypeMeta::Special<E> : public Typed<E> {
    protected:
    
        using ThisMeta  = TypeMeta::Special<E>;
        using MyEnum    = E;
        
        
        Special(std::string_view zName, const std::source_location&sl, id_t i=AUTO_ID) : Typed<E>(zName, sl, i) 
        {
            //Meta::set(Flag::ENUM);
            TypeMeta::m_write   = &ThisMeta::format_handler;
            TypeMeta::m_print   = &ThisMeta::format_handler;
            TypeMeta::m_parse   = &ThisMeta::parse_handler;
        }
        
    private:
        static void     format_handler(Stream& str, const void* me)
        {
            static const auto& em = enumeration<E>();
            str << em.key(*(const E*) me);
        }

        static std::error_code  parse_handler(void * me, const std::string_view& txt)
        {
            static const auto& em = enumeration<E>();
            auto x = em.value(txt);
            if(!x)
                return x.error();
            *(E*) me = *x;
            return {};
        }
    };
}
