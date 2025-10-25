////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "LuaVM.hpp"
#include "LuaVM.hxx"
#include "logging.hpp"
#include "lualua.hpp"

#include <filesystem>
#include <yq/lua/errors.hpp>
#include <lua.hpp>

namespace yq {

    static void luaWarn(void*, const char* msg, int)
    {
        luaWarning << msg;
    }


    LuaVM::LuaVM()
    {
        m_lua   = luaL_newstate();
        lua_setwarnf(m_lua, luaWarn, nullptr);
        luaL_openlibs(m_lua);
        set_global("**vm", this);
    }
    
    LuaVM::~LuaVM()
    {
        if(m_lua){
            lua_close(m_lua);
            m_lua   = nullptr;
        }
    }

    std::error_code    LuaVM::execute(const std::string& str)
    {
        if(!m_lua){
            luaWarning << "Invalid LuaVM";
            return errors::lua_badvm();
        }
        
        return lua::errored(luaL_dostring(m_lua, str.c_str()));
    }
    
    std::error_code    LuaVM::execfile(const std::filesystem::path&  fp)
    {
        if(!m_lua){
            luaWarning << "Invalid LuaVM";
            return errors::lua_badvm();
        }
        
        return lua::errored(luaL_dofile(m_lua, fp.c_str()));
    }

    std::error_code    LuaVM::garbage_collect()
    {
        if(!m_lua){
            luaWarning << "Invalid LuaVM";
            return errors::lua_badvm();
        }

        return lua::errored(lua_gc(m_lua, LUA_GCCOLLECT));
    }
    
    std::error_code    LuaVM::garbage_restart()
    {
        if(!m_lua){
            luaWarning << "Invalid LuaVM";
            return errors::lua_badvm();
        }
        return lua::errored(lua_gc(m_lua, LUA_GCRESTART));
    }
    
    boolean_x   LuaVM::garbate_running() const
    {
        if(!m_lua){
            luaWarning << "Invalid LuaVM";
            return errors::lua_badvm();
        }
        return static_cast<bool>(lua_gc(m_lua, LUA_GCISRUNNING));
    }
    
    std::error_code   LuaVM::garbage_stop()
    {
        if(!m_lua){
            luaWarning << "Invalid LuaVM";
            return errors::lua_badvm();
        }
        return lua::errored(lua_gc(m_lua, LUA_GCSTOP));
    }
    
    size_x LuaVM::garbage_size() const
    {
        if(!m_lua){
            luaWarning << "Invalid LuaVM";
            return errors::lua_badvm();
        }
        
        int kb  = lua_gc(m_lua, LUA_GCCOUNT);
        int b   = lua_gc(m_lua, LUA_GCCOUNTB);
        
        return (((size_t) kb) << 10) | (0x3FF & b);
    }

    std::error_code   LuaVM::set_global(const std::string&k, bool v)
    {
        if(!m_lua){
            luaWarning << "Invalid LuaVM";
            return errors::lua_badvm();
        }
        
        lua_pushboolean(m_lua, v);
        lua_setglobal(m_lua, k.c_str());
        return {};
    }
    
    std::error_code   LuaVM::set_global(const std::string&k, int v)
    {
        if(!m_lua){
            luaWarning << "Invalid LuaVM";
            return errors::lua_badvm();
        }
        
        lua_pushinteger(m_lua, v);
        lua_setglobal(m_lua, k.c_str());
        return {};
    }
    
    std::error_code   LuaVM::set_global(const std::string&k, double v)
    {
        if(!m_lua){
            luaWarning << "Invalid LuaVM";
            return errors::lua_badvm();
        }
        
        lua_pushnumber(m_lua, v);
        lua_setglobal(m_lua, k.c_str());
        return {};
    }
    
    std::error_code   LuaVM::set_global(const std::string&k, std::string_view v)
    {
        if(!m_lua){
            luaWarning << "Invalid LuaVM";
            return errors::lua_badvm();
        }
        
        lua_pushlstring(m_lua, v.data(), v.size());
        lua_setglobal(m_lua, k.c_str());
        return {};
    }
    
    std::error_code   LuaVM::set_global(const std::string&k, void* v)
    {
        if(!m_lua){
            luaWarning << "Invalid LuaVM";
            return errors::lua_badvm();
        }
        
        lua_pushlightuserdata(m_lua, v);
        lua_setglobal(m_lua, k.c_str());
        return {};
    }
    

    std::error_code     LuaVM::status() const
    {
        if(!m_lua){
            luaWarning << "Invalid LuaVM";
            return errors::lua_badvm();
        }
        return lua::errored(lua_status(m_lua));
    }
}
