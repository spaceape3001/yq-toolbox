////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/sql/preamble.hpp>
#include <0/basic/preamble.hpp>
#include <yq/container/Map.hpp>

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
        //QueryUrl(const Url&);
        //QueryUrl(const UrlView&);
        
        constexpr bool operator== (const QueryUrl&) const noexcept = default;
    };

    //Url         to_url(const QueryUrl&);
    //QueryUrl    to_query_url(const Url&);
    //QueryUrl    to_query_url(const UrlView&);

}
