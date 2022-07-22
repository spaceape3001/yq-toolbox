////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "BasicApp.hpp"
#include "Logging.hpp"
#include "TextUtils.hpp"
#include "ThreadId.hpp"

#include <basic/meta/Meta.hpp>

#include <span>
#include <string_view>
#include <cstdlib>
#include <pwd.h>
#include <unistd.h>


namespace yq {
    namespace {
        std::string             getHostName()
        {
            char        hname[HOST_NAME_MAX+1];
            gethostname(hname, sizeof(hname));
            hname[HOST_NAME_MAX]    = '\0';
            return std::string(hname);
        }
        
        std::filesystem::path   tempDir()
        {
            const char*   tmpdir  = getenv("TMPDIR");
            if(!tmpdir)
                tmpdir          = "/tmp";
            return std::filesystem::path(tmpdir) / "yquill";
        }

        std::filesystem::path homeDir()
        {
            const char* s   = getenv("HOME");
            if(s)
                return s;
            struct passwd*  pw = getpwuid(getuid());;
            if(pw)
                return pw -> pw_dir;
            return std::filesystem::path();
        }

        path_vector_t   searchPath()
        {
            path_vector_t   ret;
            const char* s   = getenv("PATH");
            if(!s){
                //  TODO ... WINDOWS!
                #ifdef __unix__
                    //  If there is no path, construct a minimal common one
                    s   = "/usr/local/bin:/usr/bin:/bin";
                #endif
            }
            
            if(s){
                vsplit(s, ':', [&](const std::string_view& s){
                    std::filesystem::path       sd(s);
                    if(!access(sd.c_str(), R_OK|X_OK))
                        ret.push_back(sd);
                });
            }
            
            return ret;
        }
    }


    BasicApp*   BasicApp::s_app  = nullptr;

    std::string_view         BasicApp::app_name()
    {
        if(s_app) [[likely]]
            return s_app -> m_exe;
        return std::string_view();
    }
    
    std::span<const char*>   BasicApp::command_line()
    {
        if(s_app) [[likely]]
            return s_app -> m_args;
        return std::span<const char*>();
    }

    std::filesystem::path        BasicApp::current_working_dir()
    {
        char        cwd[PATH_MAX+1];
        if(getcwd(cwd, PATH_MAX) != cwd) [[unlikely]]
            return std::filesystem::path();
        cwd[PATH_MAX]   = '\0';
        return std::filesystem::path(cwd);
    }

    std::filesystem::path        BasicApp::find_exe(const std::string_view k)
    {
        static const auto& search    = search_path();
        for(auto& fs : search){
            std::filesystem::path   p   = fs / k;
            if(std::filesystem::exists(p))
                return p;
        }
        return std::filesystem::path();
    }
    
    const std::string&           BasicApp::hostname()
    {
        static const std::string    s_host  = getHostName();
        return s_host;
    }
    

    const std::vector<std::filesystem::path>&  BasicApp::search_path()
    {
        static const std::vector<std::filesystem::path> s_paths = searchPath();
        return s_paths;
    }
    
    const std::filesystem::path& BasicApp::temp_dir()
    {
        static const std::filesystem::path s_temp   = tempDir();
        return s_temp;
    }
    
    const std::filesystem::path& BasicApp::user_home()
    {
        static const std::filesystem::path   s_home    = homeDir();
        return s_home;
    }

    ////////////////////////////////////////////////////////////////////////////////

    BasicApp::BasicApp(int argc, char**argv)
    {
        m_args  = std::span<const char*>((const char**) argv, argc);
        m_exe   = argv[0];
        
        if(!thread::id() && !s_app){
            s_app       = this;
            log_to_std_error( LogPriority::Debug);
            Meta::init();
        }
    }

    BasicApp::~BasicApp()
    {
        if(s_app == this)
            s_app   = nullptr;
    }

    void                     BasicApp::finalize()
    {
        if(!thread::id())
            Meta::freeze();
    }


}
