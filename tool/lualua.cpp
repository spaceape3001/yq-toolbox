////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/lua/LuaVM.hpp>
#include <yq/core/Logging.hpp>
#include <yq/process/PluginLoader.hpp>
#include <yq/meta/Meta.hpp>
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
    Meta::freeze();
    
    LuaVM   lua;
    lua.add_global_function("quit", fn_quit, "Quits the application");
    lua.init_global_functions();
    if(argc > 1){
        for(int i=1;i<argc;++i){
            lua.execfile(argv[i]);
        }
    } else {
        char    buffer[1024];
        while(std::cin.good() && !gQuit){
            memset(buffer, 0, sizeof(buffer));  // wipe existing data
            std::cout << "> ";
            std::cin.getline(buffer, sizeof(buffer));
            buffer[1023]    = '\0';             // guard against null termination
            auto ec = lua.execute(buffer);
            if(ec != std::error_code()){
                std::cout << ec.message() << "\n";
            }
        }
    }
    
    return 0;
}
