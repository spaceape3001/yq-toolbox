////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/core/DelayInit.hpp>
#include <yq/core/StreamOps.hpp>
#include <yq/lua/impl.hpp>
#include <yq/lua/logging.hpp>
#include <yq/lua/lualua.hpp>
#include <yq/lua/stream.hpp>
#include <yq/lua/info/FunctionInfo.hpp>
#include <yq/lua/info/ValueInfo.hpp>

#include <yq/math/trigonometry.hpp>
#include <yq/trait/numbers.hpp>
#include <lua.hpp>
#include <numbers>

using namespace yq;
using namespace yq::lua;

namespace {
    int     lh_absoluteValue(lua_State* l)
    {
        if(lua_gettop(l) < 1){
            complaint(l, "Insufficient arguments");
            return 0;
        }
    
        switch(lua_type(l, -1)){
        case LUA_TNUMBER:
            {
                double  v   = std::abs(lua_tonumber(l, -1));
                lua_pushnumber(l, v);
                return 1;
            }
            
            //  Others TODO
            
        default:
            warning(l, "Unrecognized argument type");
            break;
        }
        return 0;
    }

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

    int     lh_power(lua_State* l)
    {
        if(lua_gettop(l) < 2){
            complaint(l, "Insufficient arguments");
            return 0;
        }
        
            // eventually... we'll get other types (likely in the first parameter before second)
        if(lua_type(l, -1) != LUA_TNUMBER){
            warning(l, "Unrecognized argument type");
            return 0;
        }
        
        if(lua_type(l, -2) != LUA_TNUMBER){
            warning(l, "Unrecognized argument type");
            return 0;
        }
        
        double  x   = lua_tonumber(l, -2);
        double  y   = lua_tonumber(l, -1);
        lua_pushnumber(l, std::pow(x,y));
        return 1;
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
    
    int     lh_sqrt(lua_State* l)
    {
        if(lua_gettop(l) < 1){
            complaint(l, "Insufficient arguments");
            return 0;
        }

        switch(lua_type(l, -1)){
        case LUA_TNUMBER:
            {
                double  v   = std::sqrt(lua_tonumber(l, -1));
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
    
    
    ////////////////////

    void    reg_common()
    {
        if(FunctionInfo* fi = reg(GLOBAL, "abs", lh_absoluteValue)){
            fi->brief("Absolute value (ie, strip off the sign)");
        }
        if(FunctionInfo* fi = reg(GLOBAL, "cos", lh_cosine)){
            fi->brief("Cosine (Radians)");
        }
        if(FunctionInfo* fi = reg(GLOBAL, "cosd", lh_cosineD)){
            fi->brief("Cosine (Degrees)");
        }
        if(FunctionInfo* fi = reg(GLOBAL, "cot", lh_cotangent)){
            fi->brief("Cotangent (Radians)");
        }
        if(FunctionInfo* fi = reg(GLOBAL, "cotd", lh_cotangentD)){
            fi->brief("Cotangent (Degrees)");
        }
        if(FunctionInfo* fi = reg(GLOBAL, "csc", lh_cosecant)){
            fi->brief("Cosecant (Radians)");
        }
        if(FunctionInfo* fi = reg(GLOBAL, "cscd", lh_cosecantD)){
            fi->brief("Cosecant (Degrees)");
        }
        if(FunctionInfo* fi = reg(GLOBAL, "pow", lh_power)){
            fi->brief("Power (x^y)");
        }
        if(FunctionInfo* fi = reg(GLOBAL, "sec", lh_secant)){
            fi->brief("Secant (Radians)");
        }
        if(FunctionInfo* fi = reg(GLOBAL, "secd", lh_secantD)){
            fi->brief("Secant (Degrees)");
        }
        if(FunctionInfo* fi = reg(GLOBAL, "sin", lh_sine)){
            fi->brief("Sine (Radians)");
        }
        if(FunctionInfo* fi = reg(GLOBAL, "sind", lh_sineD)){
            fi->brief("Sine (Degrees)");
        }
        if(FunctionInfo* fi = reg(GLOBAL, "sqrt", lh_sqrt)){
            fi->brief("Square Root");
        }
        if(FunctionInfo* fi = reg(GLOBAL, "tan", lh_tangent)){
            fi->brief("Tangent (Radians)");
        }
        if(FunctionInfo* fi = reg(GLOBAL, "tand", lh_tangentD)){
            fi->brief("Tangent (Degrees)");
        }

        reg(GLOBAL, "pi", std::numbers::pi);
        reg(GLOBAL, "sqrt2", yq::sqrt2);
        reg(GLOBAL, "sqrt3", yq::sqrt3);
        reg(GLOBAL, "e", std::numbers::e);
    }
    YQ_INVOKE(reg_common();)
}
