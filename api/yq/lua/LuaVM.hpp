////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>
#include <yq/typedef/expected.hpp>
#include <yq/typedef/filesystem_path.hpp>
#include <system_error>

struct lua_State;
struct luaL_Reg;

namespace yq {
    class LuaVM {
    public:
    
        static LuaVM*               extract(lua_State*);
        static std::error_code      errored(int);
        
        LuaVM();
        ~LuaVM();
        
        std::error_code     execute(const std::string&);
        std::error_code     execfile(const std::filesystem::path&);
        
        std::error_code     garbage_collect();
        std::error_code     garbage_restart();
        boolean_x           garbate_running() const;
        size_x              garbage_size() const;
        std::error_code     garbage_stop();
        
        std::error_code     status() const;
        
        operator lua_State*() const { return m_lua; }
        
        std::error_code   set_global(const std::string&, bool);
        std::error_code   set_global(const std::string&, int);
        std::error_code   set_global(const std::string&, double);
        std::error_code   set_global(const std::string&, std::string_view);
        std::error_code   set_global(const std::string&, void*);
        
    private:
        LuaVM(const LuaVM&) = delete;
        LuaVM(LuaVM&&) = delete;
        LuaVM& operator=(const LuaVM&) = delete;
        LuaVM& operator=(LuaVM&&) = delete;
        
        lua_State*  m_lua   = nullptr;
    };
}
