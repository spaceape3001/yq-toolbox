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
    class GNodeResolver {
    public:
        virtual std::string     node_template(short_k, const Url&) const = 0;
        virtual Url             node_template(url_k, const std::string&) const = 0;
    };
}
