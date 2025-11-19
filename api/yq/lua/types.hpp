////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <map>
#include <set>
#include <string>
#include <system_error>
#include <vector>
#include <variant>

#include <yq/core/Flags.hpp>
#include <yq/lua/keywords.hpp>
#include <yq/text/XCase.hpp>

struct lua_State;

namespace yq {
    class Any;
    class Meta;
    class Object;
    class ObjectMeta;
    class Refable;
    class Stream;
    class TypeMeta;
    class LuaVM;
}

namespace yq::lua {
    enum class Type {
        Unknown,
        Nil,
        String,
        Boolean,
        Double,
        Integer,
        Object,
        Pointer,
        Function,
        Class,
        Module
    };

    enum class X : uint8_t {
        Type,
        Any=Type,
        Object,
        Meta,
        Const,
        Delete,
        Ref
    };
    using XFlags    = Flags<X, int32_t>;

    typedef int     (*FNLuaCallback)(lua_State*);
    typedef bool    (*FNLuaPush)(lua_State*, const void*);
    typedef bool    (*FNLuaExtract)(lua_State*, int, void*);
    typedef bool    (*FNLuaDivertor)(lua_State*, const void*);

    using value_t = std::variant<
        std::monostate,
        later_k,       
        std::string,
        bool,
        double,
        int,
        const Meta*,
        Object*,
        const Object*,
        void*,
        FNLuaCallback
    >;
    
    using type_t  = std::variant<
        std::monostate,
        std::string,
        Type,
        const TypeMeta*,
        const ObjectMeta*
    >;

    template <typename ... Args> struct LuaCallbackUpvalued {
        typedef int (*FN)(lua_State*, Args...);
    };
    
    template <typename ... Args>
    using FNLuaUpvalueHandler = LuaCallbackUpvalued<Args...>::FN;


    using cstr_xset_t   = std::set<const char*, XCase>;

#if 0
    // Idea for dealing with upvalues on function registration....
    template <typename T> 
    struct Upvalue {
        T       value;
    };
#endif

    class ArgumentInfo;
    class ClassInfo;
    class FunctionInfo;
    class Info;
    class ModuleInfo;
    class ObjectInfo;
    class TypeInfo;
    class ValueInfo;
    class Repo;
    
    template <typename> class TypedTypeInfo;
    
    using argument_info_vector_t    = std::vector<const ArgumentInfo*>;
    using function_info_map_t       = std::map<std::string,const FunctionInfo*>;
    using info_map_t                = std::map<std::string,const Info*>;
    using info_mmap_t               = std::multimap<std::string,const Info*>;
    using module_info_map_t         = std::map<std::string,const ModuleInfo*>;
    using object_info_map_t         = std::map<uint32_t, const ObjectInfo*>;
    using type_info_map_t           = std::map<uint32_t, const TypeInfo*>;
    using value_info_vector_t       = std::vector<const ValueInfo*>;
    
    using meta_module_map_t         = std::map<uint32_t, const ModuleInfo*>;

    static constexpr const int       MAX_UPVALUES    = 255;  // hardcoded in Lua
}
