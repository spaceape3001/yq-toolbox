////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/typedef/filesystem_path.hpp>
#include <span>
#include <string>
#include <string_view>
#include <vector>

namespace yq {

    class BasicApp  {
    public:
        
        //! Our application pointer
        static const BasicApp*              app() { return s_app; }
        
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
        
        BasicApp(const BasicApp&) = delete;
        BasicApp(BasicApp&&) = delete;
        BasicApp& operator=(const BasicApp&) = delete;
        BasicApp& operator=(BasicApp&&) = delete;

        std::span<const char*>      m_args;
        std::string_view            m_exe;
    };
}
