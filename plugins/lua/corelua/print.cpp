////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/core/DelayInit.hpp>
#include <yq/core/StreamOps.hpp>
#include <yq/lua/logging.hpp>
#include <yq/lua/lualua.hpp>
#include <yq/lua/stream.hpp>
#include <yq/lua/writer.hpp>
#include <yq/lua/info/FunctionInfo.hpp>
#include <yq/stream/Text.hpp>
#include <iostream>
#include <lua.hpp>

using namespace yq;
using namespace yq::lua;

namespace {
    int lh_print(lua_State* l)
    {
        int nargs   = lua_gettop(l);
        Streamer str(l);
        for(int n=1;n<=nargs;++n)
            yq::lua::write(str, l, n);
        str << '\n';
        return 0;
    }
    

    int lh_println(lua_State* l)
    {
        int nargs   = lua_gettop(l);
        Streamer str(l);
        for(int n=1;n<=nargs;++n){
            yq::lua::write(str, l, n);
            str << '\n';
        }
        return 0;
    }

    void reg_print()
    {
        if(FunctionInfo* fi = reg(GLOBAL, "print", lh_print)){
            fi->brief("Printer of printing");
            fi->help(R"VOGON(
Standard "print" redefined for the YourQuill engine so the output can be 
refined & properly redirected.
)VOGON");
        }
        if(FunctionInfo* fi = reg(GLOBAL, "println", lh_println)){
            fi->brief("Printer of printing (one per line)");
        }
    }
    
    YQ_INVOKE(reg_print();)
}
