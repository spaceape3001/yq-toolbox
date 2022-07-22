////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/trait/not_copyable.hpp>
#include <basic/trait/not_moveable.hpp>
#include <filesystem>

namespace yq {

    class PidFile : trait::not_copyable, trait::not_moveable {
    public:

        PidFile(const std::filesystem::path&, bool autoMake=true);
        ~PidFile();
        bool            first() const { return m_first; }
        void            make();
        const std::filesystem::path&    file() const { return m_file; }
        
    private:
        std::filesystem::path   m_file;
        bool                    m_first;
    };
}
