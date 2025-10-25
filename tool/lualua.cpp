////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/lua/LuaVM.hpp>
#include <yq/core/Logging.hpp>
#include <yq/meta/Meta.hpp>
#include <iostream>

using namespace yq;

int main(int argc, char* argv[])
{
    log_to_std_output();
    Meta::freeze();
    
    LuaVM   lua;
    if(argc > 1){
        for(int i=1;i<argc;++i){
            lua.execfile(argv[i]);
        }
    } else {
        char    buffer[1024];
        while(std::cin.good()){
            memset(buffer, 0, sizeof(buffer));  // wipe existing data
            std::cin.getline(buffer, sizeof(buffer));
            buffer[1023]    = '\0';             // guard against null termination
            lua.execute(buffer);
        }
    }
    
    return 0;
}
