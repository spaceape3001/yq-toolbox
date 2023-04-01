////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <io/FileResolver.hpp>
#include <io/DirUtils.hpp>
#include <basic/CollectionUtils.hpp>
#include <basic/Vector.hpp>

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
        return dir::first_child(m_paths, x);
    }

    std::vector<std::filesystem::path>  FileResolver::all_partial(std::string_view x) const
    {
        return dir::all_children(m_paths, x);
    }
}
