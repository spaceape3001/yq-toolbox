////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/container/StringMap.hpp>
#include <yq/b3fmt/typedef.hpp>

namespace yq::b3::parse {
    struct context_t {
        StringMap       m_colors;
        DoubleMap       m_units;

        std::string_view    color(const std::string& k) const;
        double              unit(const std::string& k) const;

            // Sets context, returns old one
        static const context_t*  current(const context_t*);
        
            // Gets current context (thread_local)
        static const context_t*  current();
    };
}
