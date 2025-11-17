////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/lua/writer.hpp>
#include <lua.hpp>
#include <yq/core/StreamOps.hpp>
#include <yq/text/format.hpp>

namespace yq::lua {

    std::string_view    _string(lua_State*l, int n)
    {
        size_t  sz  = 0;
        const char* v   = lua_tolstring(l, n, &sz);
        if(!v)
            return {};
        return { v, sz };
    }


    void    write_meta(Stream&str, const Meta& om, const WriteOptions& options)
    {
        str << "(meta: " << om.name() << ")";
    }

    void    write_object(Stream&str, const ObjectMeta& om, const WriteOptions& options)
    {
        str << "(object: " << om.name()<< ")";
    }

    void    write_type(Stream&str, const TypeMeta& tm, const WriteOptions& options)
    {
        str << "(" << tm.name() << ")";
    }

    void    write(Stream&str, lua_State*l, int n, const WriteOptions& options)
    {
        switch(lua_type(l, n)){
        case LUA_TNIL:
            str << "(nil)";
            break;
        case LUA_TBOOLEAN:
            str << (lua_toboolean(l,n) ? "true" : "false");
            break;
        case LUA_TNUMBER:
            if(lua_isinteger(l, n))
            str << (int64_t) lua_tointeger(l, n);
            else
                str << lua_tonumber(l,n);
            break;
        case LUA_TSTRING:
            str << _string(l,n);
            break;
        case LUA_TTABLE:
            {
                const XFlags flags  = _flags(l,n);
                const Meta* m       = _meta(l, n);
                if(m && flags(X::Meta)){
                    write_meta(str, *m, options);
                } else if(m && flags(X::Object)){
                    write_object(str, *(const ObjectMeta*)m, options);
                } else if(m && flags(X::Type)){
                    write_type(str, *(const TypeMeta*) m, options);
                } else {
                    str << "(table)";
                }
            }
            break;
        case LUA_TLIGHTUSERDATA:
            str << "(pointer: " << fmt_hex((uint64_t) lua_touserdata(l, n)) << ")";
            break;
        case LUA_TFUNCTION:
            str << "(function)";
            break;
        case LUA_TUSERDATA:
            str << "(userdata)";
            break;
        case LUA_TTHREAD:
            str << "(thread)";
            break;
        default:
            str << "(???)";
            break;
        }
    }
    
}
