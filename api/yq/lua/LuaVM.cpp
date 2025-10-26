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
#include <yq/core/Stream.hpp>
#include <yq/core/StreamOps.hpp>
#include <lua.hpp>

namespace yq {

    static void luaWarn(void*ud, const char* msg, int)
    {
        if(ud){
            (*(Stream*)ud) << msg;
        } else
            luaWarning << msg;
    }

    LuaVM::LuaVM(const LuaVMConfig& cfg)
    {
        m_lua   = luaL_newstate();
        lua_setwarnf(m_lua, luaWarn, cfg.warnings);
        luaL_openlibs(m_lua);
        lua::set(m_lua, GLOBAL, lua::VM, this);
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

    std::error_code     LuaVM::status() const
    {
        if(!m_lua){
            luaWarning << "Invalid LuaVM";
            return errors::lua_badvm();
        }
        return lua::errored(lua_status(m_lua));
    }
}
