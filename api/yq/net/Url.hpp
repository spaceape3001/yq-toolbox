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
#include <yq/meta/MetaBinder.hpp>

namespace yq {
    class Stream;

    /*! \brief URL (template)
    
        This is the template for the url.  Called Basic so we can specialize it for string vs string view.
    */
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

        //! TRUE if this url is "empty"
        bool    empty() const 
        {
            return scheme.empty() && user.empty() && pwd.empty() && host.empty() && path.empty() && query.empty() && fragment.empty() && !port;
        }
        
        // need equality & comparison (for maps)
        auto    operator<=>(const BasicUrl&) const = default;
    };

    //! Copies a view URL into a regular URL
    Url             copy(const UrlView&);
    
    //! Parses a char string to return a URL (view)
    //! \note Return are string views, thus, the original buffer needs to remain valid!
    url_view_r      to_url_view(const char*, size_t);
    
    
    //! Parses a null terminated char string to return a URL (view)
    //! \note Return are string views, thus, the original buffer needs to remain valid!
    url_view_r      to_url_view(const char*);

    //! Parses a string view to return a URL (view)
    //! \note Return are string views, thus, the original buffer needs to remain valid!
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

YQ_TYPE_DECLARE(yq::Url)

