////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Enum.hpp>
#include <yq/meta/TypeMetaWriter.hpp>
#include <yq/typedef/expected.hpp>

namespace yq {
    namespace meta_impl {
        void    format_enum(Stream&, const EnumDef&, int);
        int_x   parse_enum(const EnumDef&, std::string_view);
    }

    template <typename E>
    class TypeMeta::Special<EnumImpl<E>> : public Typed<EnumImpl<E>> {
    protected:
        using ThisMeta  = TypeMeta::Special<EnumImpl<E>>;
        using MyEnum    = EnumImpl<E>;
    
        Special(std::string_view zName, const std::source_location&sl, id_t i=AUTO_ID) : Typed<EnumImpl<E>>(zName, sl, i) 
        {
            Meta::set(Flag::ENUM);
            TypeMeta::m_write   = &ThisMeta::format_handler;
            TypeMeta::m_print   = &ThisMeta::format_handler;
            TypeMeta::m_parse   = &ThisMeta::parse_handler;
        }
        
    private:
        static void     format_handler(Stream& str, const void* me)
        {
            meta_impl::format_enum(str, *E::staticEnumInfo(), *(const int*) me);
        }
        
        static std::error_code  parse_handler(void * me, const std::string_view& txt)
        {
            auto x = meta_impl::parse_enum(*E::staticEnumInfo(), txt);
            if(!x)
                return x.error();
            *(int*) me = *x;
            return {};
        }
    };
    
    
}
