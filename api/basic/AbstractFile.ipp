////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "AbstractFile.hpp"
#include <basic/FileUtils.hpp>
#include <basic/stream/Bytes.hpp>
#include <basic/ByteArray.hpp>
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

    bool            AbstractFile::load(const std::filesystem::path& ipath)
    {
        if(!read_enabled())
            return false;
        
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
            return false;
        return load(fin, ipath);
    }


    //bool            AbstractFile::load(u8_istream&fin, const std::filesystem::path& fp)
    bool            AbstractFile::load(std::istream&fin, const std::filesystem::path& fp)
    {
        if(!read_enabled())
            return false;

        ByteArray       data;
        fin.seekg( 0, std::ios::end);
        bool    ok  = !fin.fail();
        size_t  sz  = fin.tellg();
        fin.seekg( 0, std::ios::beg);
        
        if(ok){
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

    bool            AbstractFile::load(ByteArray&&data, const std::filesystem::path& fp)
    {
        if(!read_enabled())
            return false;
        reset();
        bool ok = read(std::move(data), fp.native());
        if(ok)
            m_file  = fp;
        return ok;
    }


    bool            AbstractFile::reload()
    {
        if(m_file.empty())
            return false;
        return load(m_file);
    }


    bool            AbstractFile::save()
    {
        if(m_file.empty())
            return false;
        return save_to(m_file);
    }

    bool            AbstractFile::save_as(const std::filesystem::path& oPath)
    {
        if(save_to(oPath)){
            m_file  = oPath;
            return true;
        } else
            return false;
    }


    bool            AbstractFile::save_to(const std::filesystem::path& oPath) const
    {
        if(!write_enabled())
            return false;
        
        ByteArray               data;
        yq::stream::Bytes       output(data);
        if(!write(output))
            return false;
            
        std::filesystem::path   tmp  = oPath.string() + ".tmp";
        int         n   = 0;
        while(file_exists(tmp.c_str()))
            tmp = oPath.string() + ".tmp" + std::to_string(++n);
        std::ios_base::openmode om  = std::ios_base::out | std::ios_base::trunc;
        if(is_binary())
            om |= std::ios_base::binary;
        bool    f   = false;
        {
            std::ofstream fout(tmp, om);
            if(!fout)
                return false;
            fout.write(data.data(), data.size());
            f   = !fout.fail();
            fout.close();
        }
        if(f){
            file_backup(oPath.c_str(), "bck");
            rename(tmp.c_str(), oPath.c_str());
        } else {
            remove(tmp.c_str());
        }
        return f;
    }


    bool            AbstractFile::save_to(yq::Stream&out) const
    {   
        if(!write_enabled())
            return false;
        if(!write(out))
            return false;
        return true;
    }

    void            AbstractFile::set_file(const std::filesystem::path&p)
    {
        if(can_change_to(p))
            m_file = p;
    }
}
