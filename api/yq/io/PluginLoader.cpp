////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/io/PluginLoader.hpp>

#include <yq/io/DirUtils.hpp>
#include <yq/basic/Logging.hpp>
#include <yq/basic/ThreadId.hpp>
#include <yq/text/match.hpp>

#include <dlfcn.h>

namespace yq {


    //  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //  PID FILE
    //  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    bool  load_plugin(const filesystem_path_t&pth)
    {
        if(thread::id()){
            yCritical() << "Plugins should only be loaded on the main thread!";
            return false;
        }
    
        #ifdef NDEBUG
        try {
        #endif
            
            #if defined(WIN32)
            #error "This code is not yet defined for windows!"
            #else
            if(!dlopen(pth.c_str(), YQ_DBGREL(RTLD_LAZY|RTLD_LOCAL, RTLD_NOW|RTLD_LOCAL)))
                yError() << "Plugin (" << pth << ") failed to load.";
            return true;
            #endif
            
        #ifdef NDEBUG
        } catch(...){
            return false;
        }
        #endif
    }
    
    size_t  load_plugin_dir(const filesystem_path_t&pdir)
    {
        if(thread::id()){
            yCritical() << "Plugins should only be loaded on the main thread!";
            return 0;
        }
        
        if(!std::filesystem::is_directory(pdir)){
            yWarning() << "Not a directory " << pdir;
        }

        //  Update this for the operating system
        #if defined(WIN32)
        static constexpr const char *szExt   = ".dll";
        #else
        static constexpr const char *szExt   = ".so";
        #endif

        size_t      cnt   = 0;
        
        dir::for_all_children(pdir, dir::NO_DIRS, [&](const filesystem_path_t&p){
            if(!is_similar(p.extension().c_str(), szExt))
                return ;
            if(load_plugin(p))
                ++cnt;
        });
        return cnt;
    }
    
}
