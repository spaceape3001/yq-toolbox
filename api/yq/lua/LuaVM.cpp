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
#include <format>
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

    struct LuaVM::Function {
        std::string     name;
        CFunction       function  = nullptr;
        std::string     help;
    };

    struct LuaVM::Repo {
        std::vector<Function>   functions;
    };
    
    void  LuaVM::reg_common_global_fn(const std::string& name, CFunction fn, const std::string& helpString)
    {
        if(!fn)
            return ;
        repo().functions.push_back({name, fn, helpString});
    }

    LuaVM::Repo& LuaVM::repo()
    {
        static Repo s_repo;
        return s_repo;
    }

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

    void               LuaVM::add_global_function(const std::string& key, CFunction fn, const std::string& helpString)
    {
        m_functions.push_back({key, fn, helpString});
    }

    std::error_code    LuaVM::execute(const std::string& str)
    {
        if(!m_lua){
            luaWarning << "Invalid LuaVM";
            return errors::lua_badvm();
        }
        
        return luaL_dostring(m_lua, str.c_str()) ? errors::lua_runtime() : std::error_code();
    }
    
    std::error_code    LuaVM::execfile(const std::filesystem::path&  fp)
    {
        if(!m_lua){
            luaWarning << "Invalid LuaVM";
            return errors::lua_badvm();
        }
        
        return luaL_dofile(m_lua, fp.c_str()) ? errors::lua_runtime() : std::error_code();
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

    void   LuaVM::init_global_functions()
    {
        if(!m_lua){
            luaWarning << "Invalid LuaVM";
            return;
        }
        
        auto add = [this](const Function& fn){
            if(m_functionHelp.contains(fn.name))
                return ;
            m_functionHelp[fn.name] = fn.help;
            lua_pushcfunction(m_lua, fn.function);
            lua_setglobal(m_lua, fn.name.c_str());
        };

        for(auto& f : m_functions)
            add(f);
        for(auto& f : repo().functions)
            add(f);
    }
    
    
    /*
    const LuaVM::MetaObject*       LuaVM::meta_object(Meta::id_t id) const
    {
        auto i = m_metaObjects.find(id);
        if(i != m_metaObjects.end())
            return i->second;
        return nullptr;
    }
    
    const LuaVM::MetaObject*       LuaVM::meta_object(const ObjectMeta& om)
    {
        auto i = m_metaObjects.find(om.id());
        if(i != m_metaObjects.end())
            return i->second;
            
        MetaObject* lmt = new MetaObject;
        _init_object(*lmt, om);
        m_metaObjects[om.id()]  = lmt;
        return lmt;
    }

    const LuaVM::MetaObjectConst*  LuaVM::meta_object(Meta::id_t id, const_k) const
    {
        auto i = m_metaConstObjects.find(id);
        if(i != m_metaConstObjects.end())
            return i->second;
        return nullptr;
    }

    const LuaVM::MetaObjectConst*  LuaVM::meta_object(const ObjectMeta& om, const_k)
    {
        auto i = m_metaConstObjects.find(om.id());
        if(i != m_metaConstObjects.end())
            return i->second;

        MetaObjectConst*    lmt = new MetaObjectConst;
        _init_object(*lmt, om);
        m_metaConstObjects[om.id()] = lmt;
        return lmt;
    }

    const LuaVM::MetaType*         LuaVM::meta_type(Meta::id_t id) const
    {
        auto i = m_metaTypes.find(id);
        if(i != m_metaTypes.end())
            return i->second;
        return nullptr;
    }

    const LuaVM::MetaType*         LuaVM::meta_type(const TypeMeta& tm)
    {
        auto i = m_metaTypes.find(tm.id());
        if(i != m_metaTypes.end())
            return i->second;
            
        MetaType*   lmt = new MetaType;
        _init_type(*lmt, tm);
        m_metaTypes[tm.id()]    = lmt;
        return lmt;
    }
    */

    std::error_code     LuaVM::status() const
    {
        if(!m_lua){
            luaWarning << "Invalid LuaVM";
            return errors::lua_badvm();
        }
        return lua::errored(lua_status(m_lua));
    }
    
#if 0    
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //  ADAPTERS 

    static int      const_gc(lua_State*l)
    {
        return 0;
    }

    void    LuaVM::_init_const(MetaObjectConst& lm, const ObjectMeta& m, const_k)
    {
        l.key    = std::format("const {}", m.name());
        l.id     = m.id();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static int      object_gc(lua_State*l)
    {
        return 0;
    }

    void    LuaVM::_init_object(MetaObject& lm, const ObjectMeta& m)
    {
        l.key    = m.name();
        l.id     = m.id();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static int      type_add(lua_State*l)
    {
        return 0;
    }


    static int      type_gc(lua_State*l)
    {
        return 0;
    }


    void    LuaVM::_init_type(MetaType& l, const TypeMeta& m)
    {
        l.key    = m.name();
        l.id     = m.id();
    }
    
    #endif
    
}
