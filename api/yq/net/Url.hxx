////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/net/Url.hpp>

namespace yq {
    namespace mithril {
        class WebHtml;
    }

    template <typename S, typename T>
    requires (!std::is_same_v<S, mithril::WebHtml>)
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
}
