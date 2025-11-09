////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "LuaVM.hpp"
#include "logging.hpp"
#include "impl.hpp"
#include "lualua.hpp"

#include <filesystem>
#include <format>
#include <yq/lua/keys.hpp>
#include <yq/lua/errors.hpp>
#include <yq/core/Stream.hpp>
#include <yq/core/StreamOps.hpp>
#include <yq/meta/ArgMeta.hpp>
#include <yq/meta/ConstructorMeta.hpp>
#include <yq/meta/MethodMeta.hpp>
#include <yq/meta/ObjectMeta.hpp>
#include <yq/meta/OperatorMeta.hpp>
#include <yq/meta/PropertyMeta.hpp>
#include <yq/meta/TypeMeta.hpp>
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
        lua::set(m_lua, GLOBAL, lua::keyVM, RAW, this);
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
        if(invalid()){
            luaWarning << "Invalid LuaVM";
            return errors::lua_bad_vm();
        }
        
        return luaL_dostring(m_lua, str.c_str()) ? errors::lua_runtime() : std::error_code();
    }
    
    std::error_code    LuaVM::execfile(const std::filesystem::path&  fp)
    {
        if(invalid()){
            luaWarning << "Invalid LuaVM";
            return errors::lua_bad_vm();
        }
        
        return luaL_dofile(m_lua, fp.c_str()) ? errors::lua_runtime() : std::error_code();
    }

    std::error_code    LuaVM::garbage_collect()
    {
        if(invalid()){
            luaWarning << "Invalid LuaVM";
            return errors::lua_bad_vm();
        }

        return lua::_error(lua_gc(m_lua, LUA_GCCOLLECT));
    }
    
    std::error_code    LuaVM::garbage_restart()
    {
        if(invalid()){
            luaWarning << "Invalid LuaVM";
            return errors::lua_bad_vm();
        }
        return lua::_error(lua_gc(m_lua, LUA_GCRESTART));
    }
    
    boolean_x   LuaVM::garbate_running() const
    {
        if(invalid()){
            luaWarning << "Invalid LuaVM";
            return errors::lua_bad_vm();
        }
        return static_cast<bool>(lua_gc(m_lua, LUA_GCISRUNNING));
    }
    
    std::error_code   LuaVM::garbage_stop()
    {
        if(invalid()){
            luaWarning << "Invalid LuaVM";
            return errors::lua_bad_vm();
        }
        return lua::_error(lua_gc(m_lua, LUA_GCSTOP));
    }
    
    size_x LuaVM::garbage_size() const
    {
        if(invalid()){
            luaWarning << "Invalid LuaVM";
            return errors::lua_bad_vm();
        }
        
        int kb  = lua_gc(m_lua, LUA_GCCOUNT);
        int b   = lua_gc(m_lua, LUA_GCCOUNTB);
        
        return (((size_t) kb) << 10) | (0x3FF & b);
    }

    std::error_code     LuaVM::status() const
    {
        if(invalid()){
            luaWarning << "Invalid LuaVM";
            return errors::lua_bad_vm();
        }
        return lua::_error(lua_status(m_lua));
    }
    
}
