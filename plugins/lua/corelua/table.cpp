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
    int lh_print(lua_State*l)
    {
        int nargs   = lua_gettop(l);
        Streamer    str(l);
        for(int n=1;n<=nargs;++n){
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
        if(ModuleInfo* mi = reg(MODULE, "table")){
            mi->brief("Table utilities");
            if(FunctionInfo* fi = mi->add("print", lh_print)){
                fi->brief("Extracts keys from the tables");
            }
        }
    }
    
    YQ_INVOKE(reg_table();)
}
