////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/core/DelayInit.hpp>
#include <yq/core/StreamOps.hpp>
#include <yq/lua/info.hpp>
#include <yq/lua/logging.hpp>
#include <yq/lua/lualua.hpp>
#include <yq/lua/info/FunctionInfo.hpp>
#include <yq/lua/info/ModuleInfo.hpp>
#include <yq/meta/ObjectMeta.hpp>
#include <yq/meta/TypeMeta.hpp>
#include <yq/text/match.hpp>
#include <lua.hpp>

using namespace yq;
using namespace yq::lua;

namespace {
    
    int     lh_count(lua_State*l)
    {
        int nargs = lua_gettop(l);
        if((nargs > 0) && (lua_type(l,1) == LUA_TSTRING)){
            const char* z   = lua_tostring(l,1);
            if(is_similar(z, "type")){
                push(l, (int) TypeMeta::all().size());
                return 1;
            } else if(is_similar(z, "object")){
                push(l, (int) ObjectMeta::all().size());
                return 1;
            }
        }
        push(l, (int) Meta::all().size());
        return 1;
    }
    
    int     lh_type(lua_State*l)
    {
        int nargs = lua_gettop(l);
        for(int n=1;n<=nargs;++n){
            auto x = type_meta(l, n);
            if(x){
                push(l, META, *x);
            } else
                lua_pushnil(l);
        }
        return nargs;
    }
    
    int     lh_object(lua_State*l)
    {
        int nargs = lua_gettop(l);
        for(int n=1;n<=nargs;++n){
            auto x = object_meta(l, n);
            if(x){
                push(l, META, *x);
            } else
                lua_pushnil(l);
        }
        return nargs;
    }

    void    reg_meta()
    {
        if(ModuleInfo* mi = reg(MODULE, "meta")){
            if(FunctionInfo* fi = mi->add("count", lh_count)){
                fi->brief("Count of all meta");
            }
            if(FunctionInfo* fi = mi->add("type", lh_type)){
                fi->brief("Lookup type meta");
            }
            if(FunctionInfo* fi = mi->add("object", lh_object)){
                fi->brief("Lookup object meta");
            }
        }
    }
    
    YQ_INVOKE(reg_meta();)
}
