////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/typedef/url.hpp>
#include <yq/typedef/filesystem_path.hpp>
#include <yq/typedef/result.hpp>
#include <yq/typedef/expected.hpp>

namespace yq {
    class Stream;

    template <typename T>
    struct BasicUrl {
        T       scheme;
        T       user;
        T       pwd;
        T       host;
        T       path;
        T       query;
        T       fragment;
        int     port    = 0;
        

    //! Returns a string view based URL 
    //! \note Original URL MUST LIVE!
        operator BasicUrl<std::string_view> () const 
        requires std::is_same_v<T,std::string>
        {
            return { scheme, user, pwd, host, path, query, fragment, port };
        }

        bool    operator==(const BasicUrl&) const = default;
        bool    empty() const 
        {
            return scheme.empty() && user.empty() && pwd.empty() && host.empty() && path.empty() && query.empty() && fragment.empty() && !port;
        }
        
    };

    Url             copy(const UrlView&);
    url_view_r      to_url_view(const char*, size_t);
    url_view_r      to_url_view(const char*);
    url_view_r      to_url_view(std::string_view);
    Url             to_url(const filesystem_path_t&);
    
    
    url_view_r      as_host_port(const char*, size_t);
    url_view_r      as_host_port(std::string_view);

    std::string     to_string(const Url&);
    std::string     to_string(const UrlView&);
    
    //! Tests for a valid URL
    //! \note empty scheme is treated as valid for this context
    bool            is_valid(const UrlView&);

}
