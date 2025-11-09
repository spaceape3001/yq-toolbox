////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <yq/meta/Meta.hpp>
#include <yq/typedef/expected.hpp>
#include <yq/typedef/filesystem_path.hpp>
#include <yq/typedef/string_maps.hpp>

#include <system_error>

struct lua_State;
struct luaL_Reg;

namespace yq {
    class Stream;

    struct LuaVMConfig {
        Stream*     warnings    = nullptr;
    };

    class LuaVM {
    public:
        typedef int (*CFunction)(lua_State*);
    
    
        static LuaVM*               extract(lua_State*);
        static std::error_code      errored(int);
        
        LuaVM(const LuaVMConfig& cfg={});
        ~LuaVM();
        
        std::error_code     execute(const std::string&);
        std::error_code     execfile(const std::filesystem::path&);
        
        std::error_code     garbage_collect();
        std::error_code     garbage_restart();
        boolean_x           garbate_running() const;
        size_x              garbage_size() const;
        std::error_code     garbage_stop();
        
        std::error_code     status() const;
        
        bool                invalid() const { return !m_lua; }
        
        operator lua_State*() const { return m_lua; }
        
        //! Sets a output printer 
        //! \note This stream *MUST* remain valid as long as it's configured
        std::error_code     set_output(Stream*);
     

    private:
        LuaVM(const LuaVM&) = delete;
        LuaVM(LuaVM&&) = delete;
        LuaVM& operator=(const LuaVM&) = delete;
        LuaVM& operator=(LuaVM&&) = delete;
        
        lua_State*                  m_lua   = nullptr;
    };
}
