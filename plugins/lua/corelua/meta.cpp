////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/core/DelayInit.hpp>
#include <yq/core/StreamOps.hpp>
#include <yq/core/Object.hpp>
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
    
    int     lh_meta_count(lua_State*l)
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
    
    int     lh_meta_type(lua_State*l)
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
    
    int     lh_meta_object(lua_State*l)
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
    
    int     lha_meta_object_base(lua_State* l)
    {
        int nargs = lua_gettop(l);
        for(int n=1;n<=nargs;++n){
            auto x = object_meta(l, n);
            if(x){
                const ObjectMeta*   b   = (*x) -> base();
                if(b){
                    push(l, META, b);
                    continue;
                }
            }
            lua_pushnil(l);
        }
        return nargs;
    }

    int     lh_meta_name(lua_State* l)
    {
        int nargs = lua_gettop(l);
        for(int n=1;n<=nargs;++n){
            auto x = meta(l, n);
            if(x){
                push(l, (*x)->name());
            } else
                lua_pushnil(l);
        }
        return nargs;
    }
    
    int     lh_meta_id(lua_State *l)
    {
        int nargs = lua_gettop(l);
        for(int n=1;n<=nargs;++n){
            auto x = meta(l, n);
            if(x){
                push(l, (int) (*x)->id());
            } else
                lua_pushnil(l);
        }
        return nargs;
    }

    void    reg_meta()
    {
        if(ModuleInfo* mi = reg(MODULE, "meta")){
            if(FunctionInfo* fi = mi->add("count", lh_meta_count)){
                fi->brief("Count of all meta");
            }
            if(FunctionInfo* fi = mi->add("type", lh_meta_type)){
                fi->brief("Lookup type meta");
            }
            if(FunctionInfo* fi = mi->add("object", lh_meta_object)){
                fi->brief("Lookup object meta");
            }
            
            if(FunctionInfo* fi = mi->add("names", lh_meta_name)){
                fi->brief("Meta names");
            }

            if(FunctionInfo* fi = mi->add("ids", lh_meta_id)){
                fi->brief("Meta ids");
            }
        }
        
        if(ModuleInfo* mi = reg(META, MT_Meta)){
            if(FunctionInfo* fi = mi->add("id", lh_meta_id)){
            }
            if(FunctionInfo* fi = mi->add("name", lh_meta_name)){
            }
        }
        
        if(ModuleInfo* mi = reg(META, yq::meta<Object>())){
            if(FunctionInfo* fi = mi->add("base", lha_meta_object_base)){
            }
        }
    }
    
    YQ_INVOKE(reg_meta();)
}
