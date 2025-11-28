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

    template <typename T>
        template <typename S>
    S&      BasicUrl<T>::streamer(S& s) const
    {
        if(!scheme.empty())
            s << scheme << ':';
        
        if(!host.empty()){
            s << "//";
            if(!user.empty()){
                s << user;
                if(!pwd.empty())
                    s << ':' << pwd;
                s << '@';
            }
            s << host;
            if(port)
                s << ':' << port;
            
            if(path.empty()){
                s << '/';
            } else{
                if(path[0] != '/')
                    s << '/';
                s << path;
            }
        } else {
            if(scheme.empty()){
                s << path;
            } else {
                if(path[0] == '/')
                    s << "//";
                s << path;
            }
        }
        
        if(!query.empty())
            s << '?' << query;
        if(!fragment.empty())
            s << '#' << fragment;
        return s;
    }
    

    template <typename S, typename T>
    requires (!std::is_same_v<S, mithril::WebHtml>)
    S&              operator<<(S& s, const BasicUrl<T>& v)
    {
        return v.streamer(s);
    }
}
