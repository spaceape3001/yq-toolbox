////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>
#include <yq/typedef/url.hpp>
#include <string>

namespace yq {
    //! API for resolving nodes/elements
    struct UrlLookup {
        virtual std::string     lookup(short_k, const Url&) const = 0;
        virtual Url             lookup(url_k, const std::string&) const = 0;
    };
}
