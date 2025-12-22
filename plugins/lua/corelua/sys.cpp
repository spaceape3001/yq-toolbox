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
#include <yq/core/BasicApp.hpp>
#include <lua.hpp>

using namespace yq;

namespace {
    int lh_appdir(lua_State*l)
    {
        lua::push(l, BasicApp::app_dir().string());
        return 1;
    }

    int lh_appname(lua_State*l)
    {
        lua::push(l, BasicApp::app_name());
        return 1;
    }

    int lh_cmdline(lua_State*l)
    {
        int cnt = 1;
        lua_newtable(l);
        int n = lua_gettop(l);
        for(const char* z : BasicApp::command_line()){
            if(!z)
                continue;
            lua_pushstring(l, z);
            lua_seti(l, n, cnt);
            ++cnt;
        }
        
        return 1;
    }
    
    int lh_curdir(lua_State* l)
    {
        lua::push(l, BasicApp::current_working_dir().string());
        return 1;
    }

    int lh_hostname(lua_State*l)
    {
        lua::push(l, BasicApp::hostname());
        return 1;
    }

    int lh_initialized(lua_State*l)
    {
        lua::push(l, BasicApp::initialized());
        return 1;
    }
    
    int lh_temp_dir(lua_State* l)
    {
        lua::push(l, BasicApp::temp_dir().string());
        return 1;
    }
    
    int lh_userhome(lua_State* l)
    {
        lua::push(l, (std::string_view) BasicApp::user_home().string());
        return 1;
    }

    void reg_sys()
    {
        using namespace yq::lua;
        if(ModuleInfo* mi = reg(MODULE, "sys")){
            mi->brief("System/Application utilities");

            if(FunctionInfo* fi = mi->add("appdir", lh_appdir)){
                fi->brief("Application Directory");
            }
            

            if(FunctionInfo* fi = mi->add("cmdline", lh_cmdline)){
                fi->brief("Invocation command line (all arguments as a list)");
            }

            if(FunctionInfo* fi = mi->add("cwd", lh_curdir)){
                fi->brief("Current Working Directory");
            }

            if(FunctionInfo* fi = mi->add("exe", lh_appname)){
                fi->brief("Application Executable");
            }

            if(FunctionInfo* fi = mi->add("hostname", lh_hostname)){
                fi->brief("Our current machine's hostname");
            }

            if(FunctionInfo* fi = mi->add("initialized", lh_initialized)){
                fi->brief("Detects initialization");
            }

            if(FunctionInfo* fi = mi->add("tempdir", lh_temp_dir)){
                fi->brief("Temporary Directory");
            }

            if(FunctionInfo* fi = mi->add("userhome", lh_userhome)){
                fi->brief("User's home Directory");
            }
        }
    }
    
    YQ_INVOKE(reg_sys();)
}
