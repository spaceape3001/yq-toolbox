////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/core/DelayInit.hpp>
#include <yq/core/StreamOps.hpp>
#include <yq/lua/info.hpp>
#include <yq/lua/logging.hpp>
#include <yq/lua/lualua.hpp>
#include <yq/lua/stream.hpp>
#include <yq/lua/repo.hpp>
#include <yq/lua/info/FunctionInfo.hpp>
#include <yq/lua/info/ModuleInfo.hpp>
#include <lua.hpp>

using namespace yq;
using namespace yq::lua;

namespace {
    void reg_debug()
    {
        if(ModuleInfo* mi = reg(MODULE, "debug")){
            mi->brief("Debugging utilities");
        }
    }
    
    YQ_INVOKE(reg_debug();)
}
