////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/lua/LuaVM.hpp>
#include <yq/lua/lualua.hpp>
#include <yq/core/Logging.hpp>
#include <yq/lua/info/FunctionInfo.hpp>
#include <yq/lua/info/ModuleInfo.hpp>
#include <yq/meta/Meta.hpp>
#include <yq/process/PluginLoader.hpp>
#include <iostream>

using namespace yq;

bool    gQuit   = false;

////////////////////////////////////////////////////////////////////////////////
//  LUA HELPERS

int fn_help(lua_State*)
{
    return 0;
}

int fn_quit(lua_State*)
{
    gQuit   = true;
    return 0;
}

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
    log_to_std_output();
    Meta::init();
    load_plugin_dir("plugin/lua");
    
    yq::lua::reg(GLOBAL, "quit", fn_quit) -> brief("Quits the application");
    yq::lua::reg(GLOBAL, "help", fn_help) -> brief("Help");
    yq::lua::reg(GLOBAL, "print", lua::lh_write_cout) -> brief("Help");
    
    Meta::freeze();
    
    LuaVM   L;
    lua::configure(L);
    
    if(argc > 1){
        for(int i=1;i<argc;++i){
            L.execfile(argv[i]);
        }
    } else {
        char    buffer[1024];
        while(std::cin.good() && !gQuit){
            memset(buffer, 0, sizeof(buffer));  // wipe existing data
            std::cout << "> ";
            std::cin.getline(buffer, sizeof(buffer));
            buffer[1023]    = '\0';             // guard against null termination
            auto ec = L.execute(buffer);
            if(ec != std::error_code()){
                std::cout << ec.message() << "\n";
            }
        }
    }
    
    return 0;
}
