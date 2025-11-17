////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <lua.hpp>

#include <yq/lua/push.hpp>
#include <yq/lua/extract.hxx>

// template based standard handlers

namespace yq::lua {
    template <typename Obj>
    int  lh_obj_meta_as(lua_State*l)
    {
        if(!l)
            return 0;
        int nargs   = lua_gettop(l);
        for(int n=1;n<=nargs;++n){
            auto x = object_meta_as<Obj>(l, n);
            if(x){
                push(l, META, *x);
            } else
                lua_pushnil(l);
        }
        return nargs;
    }
}
