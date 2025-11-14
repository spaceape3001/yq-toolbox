////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/core/DelayInit.hpp>
#include <yq/lua/lualua.hxx>

using namespace yq;

namespace {
    bool  lh_push_boolean(lua_State* l, const bool& value)
    {
        lua_pushboolean(l, value);
        return true;
    }
    
    bool lh_push_string(lua_State*l, const std::string& value)
    {
        lua_pushstring(l, value.c_str());
        return true;
    }

    void reg_stdtypes()
    {
        if(auto* ti = lua::reg<bool>()){
            ti -> pusher(lh_push_boolean);
        }
        if(auto* ti = lua::reg<std::string>()){  
            ti -> pusher(lh_push_string);
        }
    }
    
    YQ_INVOKE(reg_stdtypes();)
}
