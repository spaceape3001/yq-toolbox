////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////


#pragma once
#include <bits/fs_fwd.h>
#include <bits/fs_path.h>
#include <iosfwd>
#include <basic/preamble.hpp>


namespace yq {

    /*! \brief Root of SMALL files

        \note SMALL FILES!  This class is intended to be a helper for SMALL files, ones that fit easily into memory.  
            We're talking KB size, not MB+!
    */
    class AbstractFile {
    public:

        const std::filesystem::path&    file() const { return m_file; }

        void            clear();

        bool            load(const std::filesystem::path&);
        bool            load(std::istream&, const std::filesystem::path& fp=std::filesystem::path());
        //bool            load(u8_istream&, const std::filesystem::path& fp=std::filesystem::path());
        /*! \brief Loads the data
        
            \note   This may/will be DESTRUCTIVE to the buffer, if important, make a copy.
        */
        bool            load(ByteArray&& buffer, const std::filesystem::path& fp=std::filesystem::path());
        
        /*! \brief Reloads
        
            \note this can do a *CLEAR* so a false may leave the structure in a bad state!
        */
        bool            reload();

        bool            save();
        
        //  Saves to the specified file and changes the filename (if different)
        bool            save_as(const std::filesystem::path&);
        
        //  Saves to the specified file WITHOUT changing the file
        bool            save_to(const std::filesystem::path&) const;

        bool            save_to(yq::Stream&) const;
        //bool            save_to(Vector<char>&);
        
        void            set_file(const std::filesystem::path&);
        
        
    protected:
        virtual void    reset() {}
        virtual bool    can_change_to(const std::filesystem::path&) { return true; }
        
        /*! \brief  Sub-classes extend this for "reading" the data
        
            \param[in]  buffer  The file data, this will be null-terminated (always).  However, if you're binary, this
                        could easily have MULTIPLE null values.
        */
        virtual bool    read(ByteArray&&, std::string_view fname) = 0;
        virtual bool    write(yq::Stream&) const = 0;
        virtual bool    is_binary() const { return false; }

        virtual bool    read_enabled() const { return true; }
        virtual bool    write_enabled() const { return true; }

        AbstractFile();
        ~AbstractFile();

    private:
        std::filesystem::path   m_file;
    };


}
