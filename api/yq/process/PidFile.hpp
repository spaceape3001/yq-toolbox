////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/typedef/filesystem_path.hpp>

namespace yq {
    
    /*! \brief Class for making/keeping a PID file open
    
        A PID file is something to let other invocations of the same program know 
        that there's a currently running process.  Best to put these in a temporary
        location that'll be cleared out on reboots.
    */
    class PidFile {
    public:

        //! Constructor, requires a filepath to the PID file
        PidFile(const std::filesystem::path&, bool autoMake=true);
        
        //! Destructor
        ~PidFile();
        
        //! True if we're the first process (ie, the file wasn't there on construction)
        bool            first() const { return m_first; }
        void            make();
        const std::filesystem::path&    file() const { return m_file; }
        
    private:
        std::filesystem::path   m_file;
        bool                    m_first;
        
        PidFile(const PidFile&) = delete;
        PidFile(PidFile&&) = delete;
        PidFile& operator=(const PidFile&) = delete;
        PidFile& operator=(PidFile&&) = delete;
    };
}
