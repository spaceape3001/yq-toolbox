////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/core/Logging.hpp>
#include <yq/lua/logging.hpp>
#include <yq/lua/LuaVM.hpp>
#include <yq/lua/lualua.hpp>
#include <yq/lua/keys.hpp>
#include <yq/lua/info/FunctionInfo.hpp>
#include <yq/lua/info/ModuleInfo.hpp>
#include <yq/meta/Meta.hpp>
#include <yq/process/PluginLoader.hpp>
#include <yq/stream/StdError.hpp>
#include <yq/stream/StdOutput.hpp>
#include <yq/text/format.hpp>
#include <iostream>

using namespace yq;
using namespace yq::lua;
using namespace yq::stream;

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
    lua_initialize();
    load_plugin_dir("plugin/lua");
    StdOutput           stdOut;
    StdError            stdErr;
    
    reg(GLOBAL, "quit", fn_quit) -> brief("Quits the application");
    
    Meta::freeze();
    
    LuaVM   L;
    set(L, GLOBAL, keyOutput, RAW, (Stream*) &stdOut);
    set(L, GLOBAL, keyError, RAW, (Stream*) &stdErr);
    set(L, GLOBAL, keyWarning, RAW, (Stream*) &stdOut);
    
    if(auto p = yq::lua::stream(L, OUTPUT); p != &stdOut){
        std::cerr << "Failed to get the output stream (claims: " << fmt_hex((uint64_t) p) << ")\n";
    }
    if(yq::lua::stream(L, WARNING) != &stdOut){
        std::cerr << "Failed to get the warning stream\n";
    }
    if(yq::lua::stream(L, ERROR) != &stdErr){
        std::cerr << "Failed to get the error stream\n";
    }
    
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
