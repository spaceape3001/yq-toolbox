////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/text/IgCase.hpp>
#include <yq-toolbox/typedef/string_maps.hpp>

namespace yq {
    /*! \brief Url with query parameter map (instead of pure string)
    */
    struct QueryUrl {
        std::string       scheme;
        std::string       user;
        std::string       pwd;
        std::string       host;
        std::string       path;
        string_map_t      query;
        std::string       fragment;
        int               port    = 0;
        
        QueryUrl() {}
        constexpr bool operator== (const QueryUrl&) const noexcept = default;
    };
}
