////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/core/DelayInit.hpp>
#include <yq/lua/logging.hpp>
#include <yq/lua/lualua.hpp>
#include <yq/lua/register.hpp>
#include <yq/lua/info/FunctionInfo.hpp>
#include <yq/lua/info/ModuleInfo.hpp>
#include <yq/lua/info/ValueInfo.hpp>
#include <yq/math/trigonometry.hpp>
#include <lua.hpp>

using namespace yq;
using namespace yq::lua;

namespace {

    int     lh_cosecant(lua_State* l)
    {
        if(lua_gettop(l) < 1){
            complaint(l, "Insufficient arguments");
            return 0;
        }

        switch(lua_type(l, -1)){
        case LUA_TNUMBER:
            {
                double  v   = csc(Radian{lua_tonumber(l, -1)});
                lua_pushnumber(l, v);
                return 1;
            }
        default:
            warning(l, "Unrecognized argument type");
            break;
        }

        return 0;
    }

    int     lh_cosecantD(lua_State* l)
    {
        if(lua_gettop(l) < 1){
            complaint(l, "Insufficient arguments");
            return 0;
        }

        switch(lua_type(l, -1)){
        case LUA_TNUMBER:
            {
                double  v   = csc(Degree{lua_tonumber(l, -1)});
                lua_pushnumber(l, v);
                return 1;
            }
        default:
            warning(l, "Unrecognized argument type");
            break;
        }

        return 0;
    }

    int     lh_cosine(lua_State* l)
    {
        if(lua_gettop(l) < 1){
            complaint(l, "Insufficient arguments");
            return 0;
        }

        switch(lua_type(l, -1)){
        case LUA_TNUMBER:
            {
                double  v   = std::cos(lua_tonumber(l, -1));
                lua_pushnumber(l, v);
                return 1;
            }
        default:
            warning(l, "Unrecognized argument type");
            break;
        }

        return 0;
    }

    int     lh_cosineD(lua_State* l)
    {
        if(lua_gettop(l) < 1){
            complaint(l, "Insufficient arguments");
            return 0;
        }

        switch(lua_type(l, -1)){
        case LUA_TNUMBER:
            {
                double  v   = std::cos(lua_tonumber(l, -1)*def::degree);
                lua_pushnumber(l, v);
                return 1;
            }
        default:
            warning(l, "Unrecognized argument type");
            break;
        }

        return 0;
    }


    int     lh_cotangent(lua_State* l)
    {
        if(lua_gettop(l) < 1){
            complaint(l, "Insufficient arguments");
            return 0;
        }

        switch(lua_type(l, -1)){
        case LUA_TNUMBER:
            {
                double  v   = cot(Radian{lua_tonumber(l, -1)});
                lua_pushnumber(l, v);
                return 1;
            }
        default:
            warning(l, "Unrecognized argument type");
            break;
        }

        return 0;
    }

    int     lh_cotangentD(lua_State* l)
    {
        if(lua_gettop(l) < 1){
            complaint(l, "Insufficient arguments");
            return 0;
        }

        switch(lua_type(l, -1)){
        case LUA_TNUMBER:
            {
                double  v   = cot(Degree{lua_tonumber(l, -1)});
                lua_pushnumber(l, v);
                return 1;
            }
        default:
            warning(l, "Unrecognized argument type");
            break;
        }

        return 0;
    }



    int     lh_secant(lua_State* l)
    {
        if(lua_gettop(l) < 1){
            complaint(l, "Insufficient arguments");
            return 0;
        }

        switch(lua_type(l, -1)){
        case LUA_TNUMBER:
            {
                double  v   = sec(Radian{lua_tonumber(l, -1)});
                lua_pushnumber(l, v);
                return 1;
            }
        default:
            warning(l, "Unrecognized argument type");
            break;
        }

        return 0;
    }

    int     lh_secantD(lua_State* l)
    {
        if(lua_gettop(l) < 1){
            complaint(l, "Insufficient arguments");
            return 0;
        }

        switch(lua_type(l, -1)){
        case LUA_TNUMBER:
            {
                double  v   = sec(Degree{lua_tonumber(l, -1)});
                lua_pushnumber(l, v);
                return 1;
            }
        default:
            warning(l, "Unrecognized argument type");
            break;
        }

        return 0;
    }

    int     lh_sine(lua_State* l)
    {
        if(lua_gettop(l) < 1){
            complaint(l, "Insufficient arguments");
            return 0;
        }
        
        switch(lua_type(l, -1)){
        case LUA_TNUMBER:
            {
                double  v   = std::sin(lua_tonumber(l, -1));
                lua_pushnumber(l, v);
                return 1;
            }
            break;
        default:
            warning(l, "Unrecognized argument type");
            break;
        }
    
        return 0;
    }

    int     lh_sineD(lua_State* l)
    {
        if(lua_gettop(l) < 1){
            complaint(l, "Insufficient arguments");
            return 0;
        }

        switch(lua_type(l, -1)){
        case LUA_TNUMBER:
            {
                double  v   = std::sin(lua_tonumber(l, -1)*def::degree);
                lua_pushnumber(l, v);
                return 1;
            }
            break;
        default:
            warning(l, "Unrecognized argument type");
            break;
        }

        return 0;
    }


    int     lh_tangent(lua_State* l)
    {
        if(lua_gettop(l) < 1){
            complaint(l, "Insufficient arguments");
            return 0;
        }

        switch(lua_type(l, -1)){
        case LUA_TNUMBER:
            {
                double  v   = std::tan(lua_tonumber(l, -1));
                lua_pushnumber(l, v);
                return 1;
            }
        default:
            warning(l, "Unrecognized argument type");
            break;
        }

        return 0;
    }

    int     lh_tangentD(lua_State* l)
    {
        if(lua_gettop(l) < 1){
            complaint(l, "Insufficient arguments");
            return 0;
        }

        switch(lua_type(l, -1)){
        case LUA_TNUMBER:
            {
                double  v   = std::tan(lua_tonumber(l, -1)*def::degree);
                lua_pushnumber(l, v);
                return 1;
            }
        default:
            warning(l, "Unrecognized argument type");
            break;
        }

        return 0;
    }
    
        
    void    reg_trigonometry()
    {
        if(ModuleInfo* mi = reg(MODULE, "math")){
            if(FunctionInfo* fi = mi->add("cos", lh_cosine)){
                fi->brief("Cosine (Radians)");
            }
            if(FunctionInfo* fi = mi->add("cosd", lh_cosineD)){
                fi->brief("Cosine (Degrees)");
            }
            if(FunctionInfo* fi = mi->add("cot", lh_cotangent)){
                fi->brief("Cotangent (Radians)");
            }
            if(FunctionInfo* fi = mi->add("cotd", lh_cotangentD)){
                fi->brief("Cotangent (Degrees)");
            }
            if(FunctionInfo* fi = mi->add("csc", lh_cosecant)){
                fi->brief("Cosecant (Radians)");
            }
            if(FunctionInfo* fi = mi->add("cscd", lh_cosecantD)){
                fi->brief("Cosecant (Degrees)");
            }
            if(FunctionInfo* fi = mi->add("sec", lh_secant)){
                fi->brief("Secant (Radians)");
            }
            if(FunctionInfo* fi = mi->add("secd", lh_secantD)){
                fi->brief("Secant (Degrees)");
            }
            if(FunctionInfo* fi = mi->add("sin", lh_sine)){
                fi->brief("Sine (Radians)");
            }
            if(FunctionInfo* fi = mi->add("sind", lh_sineD)){
                fi->brief("Sine (Degrees)");
            }
            if(FunctionInfo* fi = mi->add("tan", lh_tangent)){
                fi->brief("Tangent (Radians)");
            }
            if(FunctionInfo* fi = mi->add("tand", lh_tangentD)){
                fi->brief("Tangent (Degrees)");
            }
        }
    }
    
    YQ_INVOKE(reg_trigonometry();)
}

