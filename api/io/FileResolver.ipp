////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <io/FileResolver.hpp>
#include <io/DirUtils.hpp>
#include <0/basic/CollectionUtils.hpp>
#include <0/basic/Vector.hpp>

#include <0/basic/Logging.hpp>

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

    void    FileResolver::add_path(const std::filesystem::path& p)
    {
        m_paths.push_back(p);
    }
    
    std::filesystem::path       FileResolver::resolve(std::string_view x) const
    {
        for(auto& fp : m_paths){
            std::filesystem::path   p   = fp / x;
            if(std::filesystem::exists(p))
                return p;
        }
        return std::filesystem::path();
    }
    

    std::filesystem::path       FileResolver::partial(std::string_view x) const
    {
        std::error_code ec;
        for(auto& fp : m_paths){
            for(auto const& de : std::filesystem::recursive_directory_iterator(fp, ec)){
                auto dd  = de.path();
                if(!std::filesystem::is_directory(dd))
                    continue;
                auto p  = dd / x;
                if(std::filesystem::exists(p))
                    return p;
            }
        }
        return std::filesystem::path();
    }

    std::vector<std::filesystem::path>  FileResolver::all_partial(std::string_view x) const
    {
        std::vector<std::filesystem::path> ret;
        std::error_code ec;
        for(auto& fp : m_paths){
            for(auto const& de : std::filesystem::directory_iterator(fp, ec)){
                auto dd  = de.path();
                if(!std::filesystem::is_directory(dd))
                    continue;
                auto p  = dd / x;
                if(std::filesystem::exists(p))
                    ret.push_back(p);
            }
        }
        return ret;
    }
}
