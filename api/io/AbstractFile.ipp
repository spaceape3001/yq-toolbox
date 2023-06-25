////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AbstractFile.hpp"
#include <io/FileUtils.hpp>
#include <io/stream/Bytes.hpp>
#include <basic/ByteArray.hpp>
#include <io/errors.hpp>
#include <basic/errors.hpp>
#include <fstream>

namespace yq {


    AbstractFile::AbstractFile()
    {
    }

    AbstractFile::~AbstractFile()
    {
    }

    void            AbstractFile::clear()
    {
        reset();
        m_file.clear();
    }

    std::error_code  AbstractFile::load(const std::filesystem::path& ipath)
    {
        if(!read_enabled())
            return errors::not_read_enabled();
        if(ipath.empty())
            return errors::filepath_empty();
        
        //if(load_it(ipath)){
            //m_file  = ipath;
            //return true;
        //} else
            //return false;

        std::ios_base::openmode om  = std::ios_base::in;
        if(is_binary())
            om |= std::ios_base::binary;
        std::ifstream   fin(ipath, om);
        //u8_ifstream   fin(ipath, om);
        if(!fin)
            return errors::cant_open_read();
        return load(fin, ipath);
    }


    //bool            AbstractFile::load(u8_istream&fin, const std::filesystem::path& fp)
    std::error_code  AbstractFile::load(std::istream&fin, const std::filesystem::path& fp)
    {
        if(!read_enabled())
            return errors::not_read_enabled();
        if(!std::filesystem::exists(fp))
            return errors::file_not_found();

        ByteArray       data;
        fin.seekg( 0, std::ios::end);
        bool    ok  = !fin.fail();
        size_t  sz  = fin.tellg();
        fin.seekg( 0, std::ios::beg);
        
        if(ok && (sz < (1<<20ULL))){ // only take the fast way if it's 1MB or less
            data.resize(sz+1);
            fin.read(data.data(), sz);
            data[sz]    = u8'\0';
        } else {
            char     buffer[64<<10];
            while(!fin.eof() && !fin.fail()){
                fin.read(buffer, sizeof(buffer));
                size_t sz  = fin.gcount();
                data.append(buffer, sz);
            }
            data << u8'\0';
        }
        
        return load(std::move(data), fp);
    }

    std::error_code  AbstractFile::load(ByteArray&&data, const std::filesystem::path& fp)
    {
        if(!read_enabled())
            return errors::not_read_enabled();

        reset();
        std::error_code ec = read(std::move(data), fp.native());
        if(ec == std::error_code())
            m_file  = fp;
        return ec;
    }


    std::error_code  AbstractFile::reload()
    {
        if(m_file.empty())
            return errors::filepath_empty();
        reset();
        return load(m_file);
    }


    std::error_code  AbstractFile::save()
    {
        if(m_file.empty())
            return errors::filepath_empty();
        return save_to(m_file);
    }

    std::error_code  AbstractFile::save_as(const std::filesystem::path& oPath)
    {
        std::error_code ec  = save_to(oPath);
        if(ec == std::error_code())
            m_file  = oPath;
        return ec;
    }


    std::error_code  AbstractFile::save_to(const std::filesystem::path& oPath) const
    {
        if(!write_enabled())
            return errors::not_write_enabled();
        
        ByteArray               data;
        yq::stream::Bytes       output(data);
        
        std::error_code ec = write(output);
        if(ec != std::error_code())
            return ec;
            
        std::filesystem::path   tmp  = oPath.string() + ".tmp";
        int         n   = 0;
        while(file_exists(tmp.c_str()))
            tmp = oPath.string() + ".tmp" + std::to_string(++n);
        std::ios_base::openmode om  = std::ios_base::out | std::ios_base::trunc;
        if(is_binary())
            om |= std::ios_base::binary;
        std::error_code    f;
        {
            std::ofstream fout(tmp, om);
            if(!fout)
                return errors::cant_open_write();
            fout.write(data.data(), data.size());
            if(fout.fail())
                ec  = errors::failed_to_write_file();
            fout.close();
        }
        if(f == std::error_code()){
            file_backup(oPath.c_str(), "bck");
            rename(tmp.c_str(), oPath.c_str());
        } else {
            remove(tmp.c_str());
        }
        return f;
    }


    std::error_code  AbstractFile::save_to(yq::Stream&out) const
    {   
        if(!write_enabled())
            return errors::not_write_enabled();
        return write(out);
    }

    void            AbstractFile::set_file(const std::filesystem::path&p)
    {
        if(can_change_to(p))
            m_file = p;
    }
}
