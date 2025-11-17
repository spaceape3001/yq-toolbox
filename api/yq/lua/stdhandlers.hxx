////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

//#include <yq/lua/push.hpp>
#include <yq/lua/extract.hxx>
//#include <lua.hpp>

// template based standard handlers

namespace yq::lua {
    template <typename Obj>
    int  lh_object_meta_as(lua_State*l)
    {
        if(!l)
            return 0;
        int nargs   = lua_gettop(l);
        for(int n=1;n<=nargs;++n){
            auto x = ObjHelper<Obj>::object_meta_as(l, n);
            if(x){
                push(l, META, *x);
            } else
                lua_pushnil(l);
        }
        return nargs;
    }
}
