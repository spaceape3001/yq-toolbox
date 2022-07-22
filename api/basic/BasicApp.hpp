////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <basic/trait/not_copyable.hpp>
#include <basic/trait/not_moveable.hpp>

#include <filesystem>
#include <span>
#include <string>
#include <string_view>
#include <vector>

namespace yq {

    class BasicApp : trait::not_copyable, trait::not_moveable {
    public:
        
        //! Our application pointer
        static const BasicApp* const        app() { return s_app; }
        
        //! Name of the application, as provided by the command line arguments
        static std::string_view             app_name();
        
        //! Command line provided to the application
        static std::span<const char*>       command_line();
        
        //! Current working directory
        static std::filesystem::path        current_working_dir();
        
        //! Tries to find executables based on short name
        static std::filesystem::path        find_exe(const std::string_view);

        //! Our hostname
        static const std::string&           hostname();
        
        //! True if there's a BasicApp in existence
        static bool  initialized() { return s_app != nullptr; }
        
        //! Executable search path
        static const std::vector<std::filesystem::path>&  search_path();
        
        //! Prefered temporary directory
        static const std::filesystem::path& temp_dir();
        
        //! User's home directory
        static const std::filesystem::path& user_home();
        
        //! Simple constructor for the basic application
        BasicApp(int, char**);
        ~BasicApp();
        
        //! "FINALIZES" the setup
        //! This will call Meta::freeze()!
        void                        finalize();

    private:
        
        static BasicApp*            s_app;

        std::span<const char*>      m_args;
        std::string_view            m_exe;
    };
}
