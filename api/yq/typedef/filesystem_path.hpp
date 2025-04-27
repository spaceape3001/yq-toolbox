////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <bits/fs_fwd.h>
#include <bits/fs_path.h>
#include <vector>
#include <yq/container/forward.hpp>

namespace yq {
    using filesystem_path_t = std::filesystem::path;

    using PathVector        = Vector<filesystem_path_t>;
    using path_vector_t     = std::vector<filesystem_path_t>;

    inline std::filesystem::path   operator ""_fp(const char* z) 
    { 
        return std::filesystem::path(z); 
    }
}
