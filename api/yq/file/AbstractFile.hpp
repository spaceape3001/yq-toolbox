////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include <yq/typedef/filesystem_path.hpp>
#include <iosfwd>
#include <system_error>

namespace yq {
    class Stream;
    class ByteArray;

    /*! \brief Root of SMALL files

        \note SMALL FILES!  This class is intended to be a helper for SMALL files, ones that fit easily into memory.  
            We're talking KB size, not MB+!
    */
    class AbstractFile {
    public:

        //! Filepath that we loaded as.
        const filesystem_path_t&    file() const { return m_file; }

        //! Clear/reset contents of the in-memory file data-structure
        void            clear();

        //! Loads via the specified file name
        std::error_code load(const filesystem_path_t&);

        //! Loads via the specified file name/istream
        std::error_code load(std::istream&, const filesystem_path_t& fp=filesystem_path_t());
        //bool            load(u8_istream&, const filesystem_path_t& fp=filesystem_path_t());
        /*! \brief Loads the data
        
            \note   This may/will be DESTRUCTIVE to the buffer, if important, make a copy.
        */
        std::error_code load(ByteArray&& buffer, const filesystem_path_t& fp=filesystem_path_t());
        
        /*! \brief Reloads
        
            \note this can do a *CLEAR* so a false may leave the structure in a bad state!
        */
        std::error_code reload();

        std::error_code save();
        
        //  Saves to the specified file and changes the filename (if different)
        std::error_code save_as(const filesystem_path_t&);
        
        //  Saves to the specified file WITHOUT changing the file
        std::error_code save_to(const filesystem_path_t&) const;

        std::error_code save_to(yq::Stream&) const;
        //bool            save_to(Vector<char>&);
        
        void            set_file(const filesystem_path_t&);
        
        
    protected:
        virtual void    reset() {}
        virtual bool    can_change_to(const filesystem_path_t&) { return true; }
        
        /*! \brief  Sub-classes extend this for "reading" the data
        
            \param[in]  buffer  The file data, this will be null-terminated (always).  However, if you're binary, this
                        could easily have MULTIPLE null values.
        */
        virtual std::error_code read(ByteArray&&, std::string_view fname) = 0;
        virtual std::error_code write(yq::Stream&) const = 0;
        virtual bool    is_binary() const { return false; }

        virtual bool    read_enabled() const { return true; }
        virtual bool    write_enabled() const { return true; }

        AbstractFile();
        ~AbstractFile();

    private:
        filesystem_path_t   m_file;
    };


}
