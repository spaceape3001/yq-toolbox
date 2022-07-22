////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

//#include "AbstractFile.ipp"

#include <basic/FileUtils.hpp>
#include <basic/Safety.hpp>
#include <basic/Vector.hpp>
#include <basic/IterUtf8.hpp>
#include <basic/TextUtils.hpp>
#include <basic/ByteArray.hpp>
#include <basic/Result.hpp>


#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

namespace yq {

    bool        file_backup(const char* iFile, const char* suffix)
    {
        if(!file_exists(iFile))
            return true;
        std::string basis  = std::string(iFile) + "." + file_modified(iFile);
        unsigned int        i   = 0;
        std::string check(basis + '.' + suffix);
        while(file_exists(check.c_str()))
            check   = basis + '+' + std::to_string(++i) + '.' + suffix;
        return !rename(iFile, check.c_str());
    }

    ByteArray       file_bytes(const std::filesystem::path& iFile)
    {
        struct stat buf;
        memset(&buf, 0, sizeof(buf));
        if(::stat(iFile.c_str(), &buf) == -1)
            return ByteArray();
        size_t      sz  = buf.st_size;
        int fd  = open(iFile.c_str(), O_RDONLY);
        if(fd == -1)
            return ByteArray();
        
        ByteArray   ret;
        try {
            ret.resize(sz);
        } catch(const std::bad_alloc&){
            return ByteArray();
        }
        ssize_t sz2 = read(fd, ret.data(), sz);
        close(fd);
        if(sz2 < 0)
            return ByteArray();
        if(sz2 < (ssize_t) sz)
            ret.resize(sz2);
        return ret;
    }

    std::string          file_string(const std::filesystem::path&iFile)
    {
        struct stat buf;
        memset(&buf, 0, sizeof(buf));
        if(::stat(iFile.c_str(), &buf) == -1)
            return std::string();
        size_t      sz  = buf.st_size;
        int fd  = open(iFile.c_str(), O_RDONLY);
        if(fd == -1)
            return std::string();
        
        std::string   ret;
        try {
            ret.resize(sz);
        } catch(const std::bad_alloc&){
            return std::string();
        }
        ssize_t sz2 = read(fd, ret.data(), sz);
        close(fd);
        if(sz2 < 0)
            return std::string();
        if(sz2 < (ssize_t) sz)
            ret.resize(sz2);
        return ret;
    }



    bool        file_exists(const char* iFile)
    {
        return ::access(iFile, F_OK) == 0;
    }


    bool        file_exists(const std::filesystem::path& pth)
    {
        return ::access(pth.c_str(), F_OK) == 0;
    }


    std::string  file_modified(const char* iFile)
    {
        struct stat buf;
        if(::stat(iFile, &buf) != 0)
            return std::string();
            
        struct tm  mt;
        localtime_r(&buf.st_mtim.tv_sec, &mt);
        char        thetime[256];
        sprintf(thetime, "%04d%02d%02d-%02d%02d%02d.%09ld", 
            1900+mt.tm_year, 1+mt.tm_mon, 1+mt.tm_mday, 
            mt.tm_hour, mt.tm_min, mt.tm_sec, buf.st_mtim.tv_nsec
        );
        return thetime;
    }


    bool        file_readable(const char*iFile)
    {
        return ::access(iFile, F_OK | R_OK) != 0;
    }


    size_t      file_size(const char* iFile)
    {
        struct stat buf;
        memset(&buf, 0, sizeof(buf));
        if(::stat(iFile, &buf) == -1)
            return size_r();
        return buf.st_size;
    }

    SizeTimestamp file_size_and_timestamp(const std::filesystem::path& iFile)
    {
        struct stat buf;
        if(::stat(iFile.c_str(), &buf) != 0)
            return SizeTimestamp{};
        return SizeTimestamp( buf.st_size, buf.st_mtim.tv_sec, buf.st_mtim.tv_nsec );
    }

    bool    file_write(const std::filesystem::path&oFile, const char*data, size_t count)
    {
        if(count && !data)
            return false;
        
        int fd  = open(oFile.c_str(), O_CREAT|O_LARGEFILE|O_TRUNC|O_WRONLY, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
        if(fd == -1)
            return false;
        
        auto cls = safety([fd](){ close(fd); });    
        if(!count)
            return true;
        
        for(;;){
            ssize_t i   = write(fd, data, count);
            if(i <= 0)
                return false;
            if(i >= (ssize_t) count)
                return true;
            data += i;
            count -= i;
        }
    }


    bool    file_write(const std::filesystem::path&oFile, std::string_view sv)
    {
        return file_write(oFile, sv.data(), sv.size());
    }
    
    bool    file_write(const std::filesystem::path&oFile, const ByteArray& sv)
    {
        return file_write(oFile, std::string_view( sv.data(), sv.size()));
    }

    bool    file_write(const std::filesystem::path&oFile, const std::vector<char>&sv)
    {
        return file_write(oFile, std::string_view( sv.data(), sv.size()));
    }
    

    //std::filesystem::path   find_first_file(const std::filesystem::path& dir, std::string_view  name)
    //{
        //for(auto const& de : std::filesystem::directory_iterator(dname)){
            //auto p = de.path();
            //if(is_similar(p.filename().c_str(), sv))
                //return p;
        //}
        //return std::filesystem::path();
    //}




    std::string         path_sanitize(std::string_view  input)
    {
        std::string     ret;
        ret.reserve(input.size());
        
        enum Mode {
            Start       = 0,
            Token
        };
        
        
        Mode        mode    = Start;
        iter_utf8(input, [&](char32_t c){
            switch(mode){
            case Start:
                if(is_alnum(c)){
                    ret  += c;
                    mode    = Token;
                }
                break;
            case Token:
                if(c == '/'){
                    ret += '/';
                    mode    = Start;
                } else if(is_graph(c))
                    ret += c;
                break;
            }
        });
        
        return ret;
    }

    std::string_view    file_extension(std::string_view sv)
    {
        size_t      p   = sv.find_last_of('.');
        if(p == std::string_view::npos)     
            return std::string_view();  // no extension, return empty

        size_t      sl  = sv.find_last_of('/');
        if(sl == std::string_view::npos){
            if(p){
                return sv.substr(p+1);          // it's got an extension
            } else {
                return std::string_view();      // it's a hidden no-extension file, return empty;
            }
        }
        
        if(p <= sl+1)   // hidden file, no-extension, return empty
            return std::string_view();
        return sv.substr(p+1);
    }
}
