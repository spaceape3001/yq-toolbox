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
        
        operator lua_State*() const { return m_lua; }
        
        //! Sets a output printer 
        //! \note This stream *MUST* remain valid as long as it's configured
        std::error_code     set_output(Stream*);
        
        void                add_global_function(const std::string&, CFunction, const std::string& helpString="");
        //void                add_function(
        
        /*
        struct MetaType;
        struct MetaTable;
        struct MetaObject;
        struct MetaObjectConst;
        
        const MetaType*         meta_type(const TypeMeta&);
        const MetaObject*       meta_object(const ObjectMeta&);
        const MetaObjectConst*  meta_object(const ObjectMeta&, const_k);

        const MetaType*         meta_type(Meta::id_t) const;
        const MetaObject*       meta_object(Meta::id_t) const;
        const MetaObjectConst*  meta_object(Meta::id_t, const_k) const;
        */
        
        //  Call *BEFORE* going multithreaded!
        static void             reg_common_global_fn(const std::string&, CFunction, const std::string& helpString="");
        
        //  Call to initialize global functions into the lua state
        void                    init_global_functions();
        
        //! Set of all global functions
        string_set_t            global_functions() const;
        
        //! Help for given function
        std::string_view        global_function_help(const std::string&) const;
        

    private:
        LuaVM(const LuaVM&) = delete;
        LuaVM(LuaVM&&) = delete;
        LuaVM& operator=(const LuaVM&) = delete;
        LuaVM& operator=(LuaVM&&) = delete;
        
        struct Function;
        struct Repo;
        static Repo& repo();
        
        lua_State*                  m_lua   = nullptr;
        std::vector<Function>       m_functions;
        string_map_t                m_functionHelp;
        
        /*
        std::map<Meta::id_t, const MetaObjectConst*>    m_metaConstObjects;
        std::map<Meta::id_t, const MetaType*>           m_metaTypes;
        std::map<Meta::id_t, const MetaObject*>         m_metaObjects;
        
        void    _register(MetaTable&, const Meta&);
        void    _init_type(MetaType&, const TypeMeta&);
        void    _init_object(MetaObject&, const ObjectMeta&);
        void    _init_const(MetaObjectConst&, const ObjectMeta&, const_k);
        */
    };
}
