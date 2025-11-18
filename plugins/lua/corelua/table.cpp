////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/core/DelayInit.hpp>
#include <yq/core/StreamOps.hpp>
#include <yq/lua/impl.hpp>
#include <yq/lua/info.hpp>
#include <yq/lua/logging.hpp>
#include <yq/lua/lualua.hpp>
#include <yq/lua/stream.hpp>
#include <yq/lua/repo.hpp>
#include <yq/lua/info/FunctionInfo.hpp>
#include <yq/lua/info/ModuleInfo.hpp>
#include <lua.hpp>

using namespace yq;
using namespace yq::lua;

namespace {
    int lh_printtable(lua_State*l)
    {
        int nargs   = lua_gettop(l);
        Streamer    str(l);
        for(int n=1;n<=nargs;++n){
            if(lua_type(l,n) != LUA_TTABLE)
                continue;
            lua_pushnil(l);
            while(lua_next(l, n) != 0){
                yq::lua::write(str, l, -2);
                str << " => ";
                yq::lua::write(str, l, -1);
                str << '\n';
                _pop(l);
            }
        }
        return 0;
    }
    
    void reg_table()
    {
        if(FunctionInfo* fi = reg(GLOBAL, "printtable", lh_printtable)){
            fi->brief("Prints the table");
        }
    }
    
    YQ_INVOKE(reg_table();)
}
