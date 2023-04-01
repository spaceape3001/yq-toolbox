////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "QueryUrl.hpp"
#include "Url.hpp"

namespace yq {
        QueryUrl(const Url&);
        QueryUrl(const UrlView&);
        
        constexpr bool operator== (const QueryUrl&) const noexcept = default;
    };

    Url         to_url(const QueryUrl&);
    QueryUrl    to_query_url(const Url&);
    QueryUrl    to_query_url(const UrlView&);
}
