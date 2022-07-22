////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/preamble.hpp>

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
    Url             to_url(const std::filesystem::path&);
    
    
    url_view_r      as_host_port(const char*, size_t);
    url_view_r      as_host_port(std::string_view);

    std::string     to_string(const Url&);
    std::string     to_string(const UrlView&);
    
    //! Tests for a valid URL
    //! \note empty scheme is treated as valid for this context
    bool            is_valid(const UrlView&);
    
    class WebHtml;

    template <typename S, typename T>
    requires (!std::is_same_v<S, WebHtml>)
    S&              operator<<(S& s, const BasicUrl<T>& v)
    {
        if(!v.scheme.empty())
            s << v.scheme << ':';
        
        if(!v.host.empty()){
            s << "//";
            if(!v.user.empty()){
                s << v.user;
                if(!v.pwd.empty())
                    s << ':' << v.pwd;
                s << '@';
            }
            s << v.host;
            if(v.port)
                s << ':' << v.port;
            
            if(v.path.empty()){
                s << '/';
            } else{
                if(v.path[0] != '/')
                    s << '/';
                s << v.path;
            }
        } else {
            if(v.scheme.empty()){
                s << v.path;
            } else {
                if(v.path[0] == '/')
                    s << "//";
                s << v.path;
            }
        }
        
        if(!v.query.empty())
            s << '?' << v.query;
        if(!v.fragment.empty())
            s << '#' << v.fragment;
        return s;
    }

    //Stream&         operator<<(Stream&, const Url&);
    //Stream&         operator<<(Stream&, const UrlView&);
    
    //std::ostream&   operator<<(std::ostream&, const Url&);
    //std::ostream&   operator<<(std::ostream&, const UrlView&);

    //log4cpp::CategoryStream&         operator<<(log4cpp::CategoryStream&, const Url&);
    //log4cpp::CategoryStream&         operator<<(log4cpp::CategoryStream&, const UrlView&);
    

}
