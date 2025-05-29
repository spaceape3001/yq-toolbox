////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "FileResolver.hpp"
#include <yq/file/DirUtils.hpp>
#include <yq/core/Logging.hpp>

namespace yq {
    FileResolver::FileResolver()
    {
    }
    
    FileResolver::FileResolver(const FileResolver&) = default;
    FileResolver::FileResolver(FileResolver&&) = default;

    FileResolver::~FileResolver()
    {
    }

    FileResolver& FileResolver::operator=(const FileResolver&) = default;
    FileResolver& FileResolver::operator=(FileResolver&&) = default;

    bool    FileResolver::operator==(const FileResolver&b) const
    {
        return m_paths == b.m_paths;
    }

    void    FileResolver::add_path(const filesystem_path_t& p)
    {
        if(!has_path(p)){
            m_paths.push_back(p);
        }
    }

    bool    FileResolver::has_path(const filesystem_path_t& p) const
    {
        std::error_code ec; // swallow the exception
        for(auto& fp : m_paths){
            if(std::filesystem::equivalent(fp, p, ec))
                return true;
        }
        return false;
    }
    
    filesystem_path_t       FileResolver::resolve(std::string_view x) const
    {
        std::error_code ec; // swallow the exception
        for(auto& fp : m_paths){
            filesystem_path_t   p   = fp / x;
            if(std::filesystem::exists(p, ec))
                return p;
        }
        return filesystem_path_t();
    }
    

    filesystem_path_t       FileResolver::partial(std::string_view x) const
    {
        std::error_code ec; // swallow the exceptions
        for(auto& fp : m_paths){
            for(auto const& de : std::filesystem::recursive_directory_iterator(fp, ec)){
                auto dd  = de.path();
                if(!std::filesystem::is_directory(dd, ec))
                    continue;
                auto p  = dd / x;
                if(std::filesystem::exists(p, ec))
                    return p;
            }
        }
        return filesystem_path_t();
    }

    std::vector<filesystem_path_t>  FileResolver::all_partial(std::string_view x) const
    {
        std::error_code ec; // swallow the exceptions
        std::vector<filesystem_path_t> ret;
        for(auto& fp : m_paths){
            for(auto const& de : std::filesystem::directory_iterator(fp, ec)){
                auto dd  = de.path();
                if(!std::filesystem::is_directory(dd, ec))
                    continue;
                auto p  = dd / x;
                if(std::filesystem::exists(p, ec))
                    ret.push_back(p);
            }
        }
        return ret;
    }

    filesystem_path_t       FileResolver::operator()(std::string_view x) const
    {
        return resolve(x);
    }
    
    filesystem_path_t       FileResolver::operator()(full_k, std::string_view x) const
    {
        return resolve(x);
    }
    
    filesystem_path_t       FileResolver::operator()(partial_k, std::string_view x) const
    {
        return partial(x);
    }
}
