////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/errors.hpp>
#include <yq/lua/lualua.hxx>
#include <yq/core/Any.hpp>
#include <yq/core/Object.hpp>

namespace yq::lua {
    template <typename> struct Extractor;
    
    template <>
    struct Extractor<bool> {
        static boolean_x    get(lua_State*l, int n)
        {
            return boolean(l, n);
        }
    };

    template <>
    struct Extractor<double> {
        static double_x    get(lua_State*l, int n)
        {
            return double_(l, n);
        }
    };

    template <>
    struct Extractor<float> {
        static float_x    get(lua_State*l, int n)
        {
            auto x    = double_(l, n);
            if(!x)
                return unexpected(x.error());
            return (float) *x;
        }
    };

    template <>
    struct Extractor<int8_t> {
        static int8_x    get(lua_State*l, int n)
        {
            auto x   = integer(l, n);
            if(!x)
                return unexpected(x.error());
            return (int8_t) std::clamp(*x, -(1<<7), (1<<7)-1);
        }
    };

    template <>
    struct Extractor<int16_t> {
        static int16_x    get(lua_State*l, int n)
        {
            auto x   = integer(l, n);
            if(!x)
                return unexpected(x.error());
            return (int16_t) std::clamp(*x, -(1<<15), (1<<15)-1);
        }
    };

    template <>
    struct Extractor<int32_t> {
        static int32_x    get(lua_State*l, int n)
        {
            auto x   = integer(l, n);
            if(!x)
                return unexpected(x.error());
            return *x;
        }
    };

    template <>
    struct Extractor<uint8_t> {
        static uint8_x    get(lua_State*l, int n)
        {
            auto x   = integer(l, n);
            if(!x)
                return unexpected(x.error());
            return (uint8_t) std::clamp(*x, 0, 0xFF);
        }
    };

    template <>
    struct Extractor<uint16_t> {
        static uint16_x    get(lua_State*l, int n)
        {
            auto x   = integer(l, n);
            if(!x)
                return unexpected(x.error());
            return (uint16_t) std::clamp(*x, 0, 0xFFFF);
        }
    };

    template <>
    struct Extractor<uint32_t> {
        static uint32_x    get(lua_State*l, int n)
        {
            auto x   = integer(l, n);
            if(!x)
                return unexpected(x.error());
            return (uint32_t) std::clamp(*x, 0, 0x7FFFFFFF);
        }
    };

    template <>
    struct Extractor<std::string>{
        static string_x get(lua_State* l, int n)
        {
            auto x = string(l, n);
            if(!x)
                return unexpected(x.error());
            return std::string(*x);
        }
    };
    
    template <>
    struct Extractor<std::string_view> {
        static string_view_x get(lua_State* l, int n)
        {
            return string(l, n);
        }
    };
    
    template <>
    struct Extractor<Object*> {
        static object_ptr_x  get(lua_State*l, int n)
        {
            return object(l, n);
        }
    };
    
    template <>
    struct Extractor<const Object*> {
        static object_cptr_x   get(lua_State*l, int n)
        {
            return object(l, n);
        }
    };

    template <typename T>
    requires (!std::derived_from<T, Object>)
    struct Extractor<T*> {
        static Expect<T*>   get(lua_State*l, int n)
        {
            auto x = pointer(l, n);
            if(!x)
                return unexpected(x.error());
            return (T*) *x;
        }
    };

    template <typename T>
    requires (!std::derived_from<T, Object>)
    struct Extractor<const T*> {
        static Expect<const T*>   get(lua_State* l, int n)
        {
            auto x = pointer(l, n);
            if(!x)
                return unexpected(x.error());
            return (const T*) *x;
        }
    };
    
    template <typename Obj>
    requires (std::is_base_of_v<Object, Obj> && !std::is_same_v<Obj,Object>)
    struct Extractor<Obj*> {
        static Expect<Obj*>   get(lua_State* l, int n)
        {
            return object_as<Obj>(l, n);
        }
    };

    template <typename Obj>
    requires (std::is_base_of_v<Object, Obj> && !std::is_same_v<Obj,Object>)
    struct Extractor<const Obj*> {
        static Expect<const Obj*>   get(lua_State* l, int n)
        {
            return object_as<Obj>(l, n, CONST);
        }
    };

    template <>
    struct Extractor<void*> {
        static void_ptr_x get(lua_State* l, int n)
        {
            return voidptr(l, n);
        }
    };

    template <>
    struct Extractor<const void*> {
        static void_cptr_x get(lua_State* l, int n)
        {
            auto x = voidptr(l, n);
            if(!x)
                return unexpected(x.error());
            return *x;
        }
    };
    
    // Any... others... TODO
}
