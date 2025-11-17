////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/lua/info/TypeInfo.hpp>
#include <yq/meta/Meta.hpp>

namespace yq::lua {
    template <typename T>
    class TypedTypeInfo : public TypeInfo {
    public:
        //  To avoid nasty things... NEVER DO MEMBERS/VIRTUAL OVERRIDES IN HERE!
        //  It needs to work with a type info being allocated (& casted into a typed type).
    
        TypedTypeInfo() : TypeInfo(::yq::meta<T>()){}
        
        typedef bool (*FNPush)(lua_State*, const T&);
        typedef bool (*FNExtract)(lua_State*, int, T&);
        
        void    pusher(FNPush fn)
        {
            if(!fn)
                return ;
            if(!Meta::thread_safe_write())
                return;
            TypeInfo::m_pusher      = (FNLuaPush) fn;
        }
        
        void    extractor(FNExtract fn)
        {
            if(!fn)
                return;
            if(!Meta::thread_safe_write())
                return;
            TypeInfo::m_extractor   = (FNLuaExtract) fn;
        }
    };
}
