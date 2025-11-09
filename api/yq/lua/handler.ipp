////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/lua/handler.hpp>
#include <yq/lua/impl.hpp>
#include <yq/lua/writer.hpp>
#include <yq/core/StreamOps.hpp>
#include <yq/stream/Text.hpp>
#include <iostream>

namespace yq::lua {
    int lh_gc_object(lua_State* l)
    {
        if(!_gc(l, 1, OBJECT))
            return 0;
        _pop(l);
        return -1;
    }

    int lh_write_cerr(lua_State* l)
    {
        int nargs   = lua_gettop(l);
        std::string data;
        {
            stream::Text    str(data);
            for(int n=1;n<=nargs;++n)
                write(str, l, n);
            str << '\n';
        }
        std::cerr << data;
        return 0;
    }
    
    int lh_write_cout(lua_State* l)
    {
        int nargs   = lua_gettop(l);
        std::string data;
        {
            stream::Text    str(data);
            for(int n=1;n<=nargs;++n)
                write(str, l, n);
            str << '\n';
        }
        std::cout << data;
        return 0;
    }
    
    int lh_write_stream(lua_State* l)
    {
        int nargs   = lua_gettop(l);
        auto x = lua::voidptr(l, UPVALUE, 1);
        if(!x)
            return 0;
        if(!*x)
            return 0;
        Stream& s   = * (Stream*) *x;
        for(int n=1;n<=nargs;++n)
            write(s, l, n);
        s << '\n';
        return 0;
    }
    
}
