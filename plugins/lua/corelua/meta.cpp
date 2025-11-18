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
#include <yq/lua/info/ObjectInfo.hpp>
#include <yq/lua/info/TypeInfo.hpp>
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
    
    int     lh_meta_description(lua_State *l)
    {
        int nargs = lua_gettop(l);
        for(int n=1;n<=nargs;++n){
            auto x = meta(l, n);
            if(x){
                push(l, (*x)->description());
            } else
                lua_pushnil(l);
        }
        return nargs;
    }
    
    int     lh_meta_get(lua_State *l)
    {
        int nargs = lua_gettop(l);
        for(int n=1;n<=nargs;++n){
            auto x = meta(l, n);
            if(x){
                push(l, META, *x);
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
    
    int     lh_meta_object_base(lua_State* l)
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

    int     lh_meta_tagged(lua_State*l)
    {
        if(lua_gettop(l) < 2)
            return 0;
        
        auto x = meta(l,1);
        if(!x)
            return 0;
        
        switch(lua_type(l, 2)){
        case LUA_TNUMBER:
            lua_pushboolean(l, (*x)->tagged(lua_tointeger(l, 2)));
            return 1;
        case LUA_TSTRING:
            lua_pushboolean(l, (*x)->tagged(lua_tostring(l,2)));
            return 1;
        default:
            return 0;
        }
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
    
    int lh_meta(lua_State*l)
    {
        int nargs = lua_gettop(l);
        for(int n=1;n<=nargs;++n){
            auto x = meta(l, n);
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
            if(FunctionInfo* fi = mi->add("count", lh_meta_count)){
                fi->brief("Count of all meta");
            }

            if(FunctionInfo* fi = mi->add("get", lh_meta_get)){
                fi->brief("Get meta (by ID and/or extract)");
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

            if(FunctionInfo* fi = mi->add("tagged", lh_meta_tagged)){
                fi->brief("Tests for tag on meta");
            }
        }
        
        if(ModuleInfo* mi = reg(META, MT_Meta)){
            if(FunctionInfo* fi = mi->add("description", lh_meta_description)){
                fi->brief("Description for meta");
            }
            if(FunctionInfo* fi = mi->add("id", lh_meta_id)){
                fi->brief("ID for meta");
            }
            if(FunctionInfo* fi = mi->add("name", lh_meta_name)){
                fi->brief("Name for meta");
            }
            if(FunctionInfo* fi = mi->add("tagged", lh_meta_tagged)){
                fi->brief("Tests for tag on meta");
            }
        }
        
        if(ModuleInfo* mi = reg(META, yq::meta<Object>())){
            if(FunctionInfo* fi = mi->add("base", lh_meta_object_base)){
                fi->brief("Base meta");
            }
        }
        
        if(ObjectInfo* mi = reg(yq::meta<Object>())){
            if(FunctionInfo*fi = mi->add("meta", lh_meta)){
                fi->brief("Meta for this object");
            }
        }
    }
    
    YQ_INVOKE(reg_meta();)
}
