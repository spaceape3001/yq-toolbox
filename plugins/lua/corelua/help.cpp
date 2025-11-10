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
#include <yq/lua/info/ObjectInfo.hpp>
#include <yq/lua/info/FunctionInfo.hpp>
#include <yq/lua/info/ModuleInfo.hpp>
#include <yq/lua/info/TypeInfo.hpp>
#include <yq/lua/info/ValueInfo.hpp>
#include <yq/text/basic.hpp>
#include <yq/text/format.hpp>
#include <yq/text/match.hpp>
#include <yq/text/vsplit.hpp>
#include <lua.hpp>

using namespace yq;
using namespace yq::lua;

namespace {

    void    help_top(lua_State*l, Streamer& out)
    {
        out << "Help:\n"
            << "    globals -- lists globals\n"
            << "    modules -- lists modules\n"
        ;
    }
    
    void    list_module(lua_State*l, Streamer& out, const ModuleInfo& m)
    {
        out << "Help for Module: " << m.key();
        if(!m.brief().empty())
            out << " (" << m.brief() << ")";
        out << '\n';
        
        if(!m.help().empty()){
            out << "\n";
            vsplit(m.help(), '\n', [&](std::string_view v){
                out << "    " << v << '\n';
            });
            out << '\n';
        }

        size_t  mx  = 0;
        for(auto& i : m.components())
            mx  = std::max(mx, i.first.size());

        std::string         paddata(mx+2, ' ');
        std::string_view    padder(paddata);
    
        for(auto& i : m.components()){
            out << "    " << i.first << padder.substr(i.first.size());
            if(const FunctionInfo* fn = dynamic_cast<const FunctionInfo*>(i.second)){
                out << "(function)  " << i.second->brief() << '\n';
            } else if(const ValueInfo* val = dynamic_cast<const ValueInfo*>(i.second)){
                out << "(value)     " << i.second->brief() << '\n';
            } else {
                out << "(unknown)   " << i.second->brief() << '\n';
            }
        }
    }
    
    void    help_globals(lua_State*l, Streamer& out)
    {
        const ModuleInfo*   m   = info(GLOBAL);
        if(!m)  [[unlikely]]    // we're here, so we're already registered (in the global table)
            return ;
        list_module(l, out, *m);
    }

    void    help_modules(lua_State*l, Streamer& out)
    {
        auto& modules   = Repo::instance().modules();
        if(modules.empty()){
            if(out(WARNING))
                out.warning() << "No modules found\n";
            else
                out << "Warning: No modules present\n";
        }
        for(auto& i : modules)
            out << i.first << '\n';
    }


    int     cmd_help(lua_State*l)
    {
        int         nargs   = lua_gettop(l);
        std::string cmd;
        
        if(nargs){
            auto x = string(l, 1);
            if(x)
                cmd = std::string(std::move(*x));
        }

        Streamer    out(l);
        if(!out.can_output()){
            luaWarning << "help(): No output stream!";
            return 0;
        }
        if(!out.can_warning()){
            luaWarning << "help(): No warning stream!";
        }
        if(!out.can_error()){
            luaWarning << "help(): No error stream!";
        }
        
    
        if(cmd.empty()){
            help_top(l, out);
        } else if(is_similar(cmd, "globals")){
            help_globals(l, out);
        } else if(is_similar(cmd, "modules")){
            help_modules(l, out);
        } else if(const ModuleInfo*   m  = info(MODULE, cmd.c_str())){
            list_module(l, out, *m);
        } else {
            //  more todo....
            out << "Help: Unsure what to make of \"" << cmd << "\"\n";
        }

        return 0;
    }


    void    reg_help()
    {
        reg(GLOBAL, "help", cmd_help)->brief("Help routine");
    }
    
    YQ_INVOKE(reg_help();)
}
