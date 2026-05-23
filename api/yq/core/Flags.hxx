////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Enumeration.hpp>
#include <yq/core/Flags.hpp>
#include <yq/text/vsplit.hpp>

namespace yq {
    template <typename E, typename T>
    Flags<E,T>::Flags(std::string_view sv, char sep, bool *ok)
    {
        static const auto& em = enumeration<E>();
        bool    bad = false;
        vsplit(sv, sep, [&](std::string_view v){
            auto x = em.value(v);
            if(!x){
                bad = true;
                return ;
            }
            set(*x);
        });
        if(ok)
            *ok  = !bad;
    }
    
    template <typename E, typename T>
    std::string Flags<E,T>::as_display(char sep) const
    {
        static const auto& em = enumeration<E>();
        std::string ret;
        for(E e : em.values(UNIQUE)){
            if(is_set(e)){
                if(!ret.empty())
                    ret += sep;
                ret += em.display(e);
            }
        }
        return ret;
    }

    template <typename E, typename T>
    std::string Flags<E,T>::as_string(char sep) const
    {
        static const auto& em = enumeration<E>();
        std::string ret;
        for(E e : em.values(UNIQUE)){
            if(is_set(e)){
                if(!ret.empty())
                    ret += sep;
                ret += em.key(e);
            }
        }
        return ret;
    }
}
