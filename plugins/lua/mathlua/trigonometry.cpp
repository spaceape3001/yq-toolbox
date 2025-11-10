////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/core/DelayInit.hpp>
#include <yq/core/StreamOps.hpp>
#include <yq/math/trigonometry.hpp>
#include <yq/lua/impl.hpp>
#include <yq/lua/lualua.hpp>
#include <yq/lua/logging.hpp>
#include <yq/lua/stream.hpp>
#include <yq/lua/info/FunctionInfo.hpp>
#include <lua.hpp>

using namespace yq;
using namespace yq::lua;

namespace {
    
    void    complaint(lua_State*l, std::string_view txt)
    {
        Streamer    out(l);
        out.error() << txt;
    }

    int     lh_sine(lua_State* l)
    {
        int nargs   = lua_gettop(l);
        if(nargs < 1){
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
        int nargs   = lua_gettop(l);
        if(nargs < 1){
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

    int     lh_cosine(lua_State* l)
    {
        int nargs   = lua_gettop(l);
        if(nargs < 1){
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
        int nargs   = lua_gettop(l);
        if(nargs < 1){
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

    int     lh_tangent(lua_State* l)
    {
        int nargs   = lua_gettop(l);
        if(nargs < 1){
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
        int nargs   = lua_gettop(l);
        if(nargs < 1){
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

    int     lh_cotangent(lua_State* l)
    {
        int nargs   = lua_gettop(l);
        if(nargs < 1){
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
        int nargs   = lua_gettop(l);
        if(nargs < 1){
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
        int nargs   = lua_gettop(l);
        if(nargs < 1){
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
        int nargs   = lua_gettop(l);
        if(nargs < 1){
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

    int     lh_cosecant(lua_State* l)
    {
        int nargs   = lua_gettop(l);
        if(nargs < 1){
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
        int nargs   = lua_gettop(l);
        if(nargs < 1){
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

    void    reg_trigonometry()
    {
        if(FunctionInfo* fi = reg(GLOBAL, "sin", lh_sine)){
            fi->brief("Sine (Radians)");
        }
        if(FunctionInfo* fi = reg(GLOBAL, "sind", lh_sineD)){
            fi->brief("Sine (Degrees)");
        }
        if(FunctionInfo* fi = reg(GLOBAL, "cos", lh_cosine)){
            fi->brief("Cosine (Radians)");
        }
        if(FunctionInfo* fi = reg(GLOBAL, "cosd", lh_cosineD)){
            fi->brief("Cosine (Degrees)");
        }
        if(FunctionInfo* fi = reg(GLOBAL, "tan", lh_tangent)){
            fi->brief("Tangent (Radians)");
        }
        if(FunctionInfo* fi = reg(GLOBAL, "tand", lh_tangentD)){
            fi->brief("Tangent (Degrees)");
        }
        if(FunctionInfo* fi = reg(GLOBAL, "cot", lh_cotangent)){
            fi->brief("Cotangent (Radians)");
        }
        if(FunctionInfo* fi = reg(GLOBAL, "cotd", lh_cotangentD)){
            fi->brief("Cotangent (Degrees)");
        }
        if(FunctionInfo* fi = reg(GLOBAL, "sec", lh_secant)){
            fi->brief("Secant (Radians)");
        }
        if(FunctionInfo* fi = reg(GLOBAL, "secd", lh_secantD)){
            fi->brief("Secant (Degrees)");
        }
        if(FunctionInfo* fi = reg(GLOBAL, "csc", lh_cosecant)){
            fi->brief("Cosecant (Radians)");
        }
        if(FunctionInfo* fi = reg(GLOBAL, "cscd", lh_cosecantD)){
            fi->brief("Cosecant (Degrees)");
        }
    }
    YQ_INVOKE(reg_trigonometry();)
}
