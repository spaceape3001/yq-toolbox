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
#include <yq/lua/info/ModuleInfo.hpp>
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

    ////////////////////

    void    reg_common()
    {
        if(ModuleInfo* mi = reg(MODULE, "math")){
            mi -> brief("Math Library");
            if(FunctionInfo* fi = mi->add("abs", lh_absoluteValue)){
                fi->brief("Absolute value (ie, strip off the sign)");
            }
            if(FunctionInfo* fi = mi->add("pow", lh_power)){
                fi->brief("Power (x^y)");
            }
            if(FunctionInfo* fi = mi->add("sqrt", lh_sqrt)){
                fi->brief("Square Root");
            }

            reg(GLOBAL, "pi", std::numbers::pi);
            reg(GLOBAL, "sqrt2", yq::sqrt2);
            reg(GLOBAL, "sqrt3", yq::sqrt3);
            reg(GLOBAL, "e", std::numbers::e);
        }
    }
    YQ_INVOKE(reg_common();)
}
