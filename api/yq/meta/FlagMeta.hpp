////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/errors.hpp>
#include <yq/core/Enumeration.hpp>
#include <yq/core/Flags.hpp>
#include <yq/meta/TypeMetaWriter.hpp>
#include <yq/text/vsplit.hpp>
#include <yq/core/Flags.hxx>

namespace yq {
    template <typename E, typename T>
    requires std::is_enum_v<E>
    class TypeMeta::Special<Flags<E,T>> : public Typed<Flags<E,T>> {
    protected:
    
        using ThisMeta  = TypeMeta::Special<Flags<E,T>>;
        using MyEnum    = E;
        using MyFlags   = Flags<E,T>;
        
        Special(std::string_view zName, const std::source_location&sl, id_t i=AUTO_ID) : Typed<Flags<E,T>>(zName, sl, i) 
        {
            //Meta::set(Flag::ENUM);
            TypeMeta::m_write   = &ThisMeta::write_handler;
            TypeMeta::m_print   = &ThisMeta::print_handler;
            TypeMeta::m_parse   = &ThisMeta::parse_handler;
        }
        
    private:
        static void     write_handler(Stream& str, const void* me)
        {
            str << (*(const MyFlags*) me).as_string('|');
        }

        static void     print_handler(Stream& str, const void* me)
        {
            str << (*(const MyFlags*) me).as_display('|');
        }

        static std::error_code  parse_handler(void * me, const std::string_view& txt)
        {
            bool ok = false;
            MyFlags ret(txt, '|', &ok);
            if(!ok)
                return errors::bad_argument();
            *(MyFlags*) me = ret;
            return {};
        }
    };
}
