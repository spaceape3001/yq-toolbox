////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Url.hpp"

//#include <basic/DelayInit.hpp>
//#include <basic/EnumMap.hpp>
//#include <basic/Logging.hpp>
#include <basic/StreamOps.hpp>
#include <basic/stream/Text.hpp>
#include <basic/TextUtils.hpp>
//#include <stdio.h>

namespace yq {
    url_view_r      as_host_port(const char*sz, size_t cb)
    {
        if(!sz || !cb)
            return {};

        enum Mode {
            Host1       = 0,
            Host2,
            IPv6,
            SqClose,
            Port
        };
        
        UrlView     ret;
        Mode        mode    = Host1;
        const char* z       = nullptr;
        const char* str     = nullptr;
        
        auto sstring = [&]() -> std::string_view {
            if(str && z){
                std::string_view    ret(str, z-str);
                str     = nullptr;
                return ret;
            } else
                return std::string_view();
        };
        
        for(z = sz; z < sz+cb; ++z){
            switch(mode){
            case Host1:
                str     = z;
                if(*z == '[')
                    mode    = IPv6;
                else
                    mode    = Host2;
                break;
            case Host2:
                if(*z == ':'){
                    ret.host    = sstring();
                    mode    = Port;
                }
                break;
            case IPv6:
                if(*z == ']')
                    mode     = SqClose;
                break;
            case SqClose:
                if(*z == ':'){
                    ret.host    = sstring();
                    mode        = Port;
                }
                break;
            case Port:
                if(!str)
                    str = z;
                break;
            }
        }
        
        bool        good    = true;
        
        switch(mode){
        case Host2:
        case SqClose:
            ret.host        = sstring();
            break;
        case Port:
            {
                auto    r   = to_integer(sstring());
                ret.port    = r.value;
                good        = good && r.good;
            }
            break;
        default:
            good    = false;
            break;
        }
        
        return { ret, good };
        
    }    

    url_view_r      as_host_port(std::string_view s)
    {
        return as_host_port(s.data(), s.size());
    }

    Url             copy(const UrlView& v)
    {
        return Url{ copy(v.scheme), copy(v.user), copy(v.pwd), copy(v.host), copy(v.path), copy(v.query), copy(v.fragment), v.port};
    }

    bool            is_valid(const UrlView&v)
    {
        if(v.host.empty()){
            if(!v.user.empty())
                return false;
            if(!v.pwd.empty())
                return false;
            if(!v.port)
                return false;
        } else {
            if(v.user.empty() && !v.pwd.empty())
                return false;
        }
        
        return true;
    }
    
    Url             to_url(const std::filesystem::path& pth)
    {
        return Url{ "file", std::string(), std::string(), std::string(), pth.string(), std::string(), std::string(), 0 };
    }
    
    url_view_r      to_url_view(const char* sz, size_t cb)
    {
        //  URI = scheme ":" ["//" authority] path ["?" query] ["#" fragment]
        //  authority = [userinfo "@"] host [":" port]
        
        if(!sz || !cb)
            return {};
            
        if((cb == 1) && (*sz == '/'))
            return { UrlView{ std::string_view(), std::string_view(), std::string_view(), std::string_view(), "/", std::string_view(), std::string_view(), 0 }, true };

        enum Mode {
            Start       = 0,
            Scheme,
            Colon,
            Slash1,
            Slash2,
            UserOrHost,
            PwdOrPort,
            Host1,
            Host2,
            SqOpen,
            IPv6,
            SqClose,
            Port,
            PSlash,
            Path,
            Query,
            Fragment,
            Error
        };
        
        UrlView     ret;
        
        const char* z   = nullptr;
        const char* str = nullptr;
        Mode        mode    = Start;
        std::string_view    userhost;
        
        auto sstring = [&](int n=0) -> std::string_view {
            if(str && z){
                std::string_view    ret(str, z-str+n);
                str     = nullptr;
                return ret;
            } else
                return std::string_view();
        };
        
        for(z=sz;z!=sz+cb;++z){
            switch(mode){
            case Start:
                if(*z == '.'){
                    mode    = Path;
                    str     = z;
                } else if(*z == '/'){
                    mode    = Slash1;
                } else if(is_alpha(*z)){
                    mode    = Scheme;
                    str     = z;
                } else 
                    mode    = Error;
                break;
            case Scheme:
                if(*z == ':'){
                    ret.scheme  = sstring();
                    mode    = Colon;
                } else if(!(is_alnum(*z) || (*z == '+') || (*z == '.') || (*z == '-')))
                    mode    = Error;
                break;
            case Colon:
                if(*z == '/'){
                    mode    = Slash1;
                } else {
                    str     = z;
                    mode    = Path;
                }
                break;
            case Slash1:
                if(*z == '/'){
                    mode    = Slash2;
                } else {
                    str     = z-1;
                    mode    = Path;
                }
                break;
            case Slash2:
                if(*z == '/'){
                    mode    = Path;
                    str     = z;
                } else if(*z == '['){
                    mode    = SqOpen;
                    str     = z;
                } else if(*z == '@'){
                    mode    = Error;
                } else if(*z == ':'){
                    mode    = Error;
                } else {
                    mode    = UserOrHost;
                    str     = z;
                }
                break;
            case UserOrHost:
                if(*z == '@'){
                    ret.user    = sstring();
                    mode        = Host1;
                } else if(*z == ':'){
                    mode        = PwdOrPort;
                    userhost    = sstring();
                    str         = z+1;
                } else if(*z == '/'){
                    //  it's a host....
                    ret.host    = sstring();
                    mode        = Path;
                    str         = z;
                }
                break;
            case PwdOrPort:
                if(*z == '@'){
                    // it was a user...  (with password)
                    ret.user    = userhost;
                    ret.pwd     = sstring();
                    mode        = Host1;
                } else if(*z == '/'){
                    // it was a host:port
                    ret.host    = userhost;
                    ret.port    = to_integer(sstring()).value;
                    mode        = Path;
                    str         = z;
                }
                break;
            case Host1:
                str         = z;
                if(*z == '['){
                    mode    = SqOpen;
                } else if(*z == ':'){
                    mode    = Error;
                } else {
                    mode    = Host2;
                }
                break;
            case Host2:
                if(*z == ':'){
                    ret.host    = sstring();
                    mode        = Port;
                    str         = z + 1;
                } else if(*z == '/'){
                    ret.host    = sstring();
                    mode        = Path;
                    str         = z;
                } 
                break;
            case SqOpen:
                if( *z == ']'){
                    mode        = Error;
                } else 
                    mode        = IPv6;
                break;
            case IPv6:
                if(*z == ']')
                    mode         = SqClose;
                break;
            case SqClose:
                ret.host        = sstring(1);
                if(*z == ':'){
                    mode        = Port;
                    str         = z+1;
                } else if(*z == '/'){
                    mode        = Path;
                    str         = z;
                } else
                    mode        = Error;
                break;
            case Port:
                if(*z == '/'){
                    ret.port    = to_integer(sstring()).value;
                    mode        = Path;
                    str         = z;
                } else if(!is_digit(*z)){
                    mode        = Error;
                }
                break;
            case Path:
                if(*z == '?'){
                    ret.path    = sstring();
                    mode        = Query;
                    str         = z+1;
                } else if(*z == '#'){
                    ret.path    = sstring();
                    mode        = Fragment;
                    str         = z+1;
                }
                break;
            case Query:
                if(*z == '#'){
                    ret.query  = sstring();
                    mode       = Fragment;
                    str         = z+1;
                }
                break;
            default:
                break;
            }
            
            if(mode == Error)
                return { ret, false};
        }
        
        switch(mode){
        case Scheme:
        case Colon:
        case Slash1:
        case Slash2:
            mode        = Error;
            break;
        case UserOrHost:
            ret.host    = sstring();
            break;
        case PwdOrPort:
            ret.host    = userhost;
            ret.port    = to_integer(sstring()).value;
            break;
        case Path:
            ret.path    = sstring();
            break;
        case Query:
            ret.query   = sstring();
            break;
        case Fragment:
            ret.fragment    = sstring();
            break;
        default:
            break;
        }
        
        
        return { ret, mode != Error };
    }
    
    url_view_r      to_url_view(const char*z)
    {   
        return to_url_view(z, strlen(z));
    }

    url_view_r      to_url_view(std::string_view s)
    {
        return to_url_view(s.data(), s.size());
    }

    //template <typename S>
    //void            stream(S& s, const UrlView& v)
    //{
        //if(!v.scheme.empty())
            //s << v.scheme << ':';
        
        //if(!v.host.empty()){
            //s << "//";
            //if(!v.user.empty()){
                //s << v.user;
                //if(!v.pwd.empty())
                    //s << ':' << v.pwd;
                //s << '@';
            //}
            //s << v.host;
            //if(v.port)
                //s << ':' << v.port;
            
            //if(v.path.empty()){
                //s << '/';
            //} else{
                //if(v.path[0] != '/')
                    //s << '/';
                //s << v.path;
            //}
        //} else {
            //if(v.scheme.empty()){
                //s << v.path;
            //} else {
                //if(v.path[0] == '/')
                    //s << "//";
                //s << v.path;
            //}
        //}
        
        //if(!v.query.empty())
            //s << '?' << v.query;
        //if(!v.fragment.empty())
            //s << '#' << v.fragment;
    //}


    //Stream&         operator<<(Stream&s, const UrlView&v)
    //{
        //stream(s, v);
        //return s;
    //}
    
    //Stream&         operator<<(Stream&s, const Url&v)
    //{
        //return s << (UrlView) v;
    //}

    //std::ostream&   operator<<(std::ostream&s, const UrlView& v)
    //{
        //stream(s, v);
        //return s;
    //}
    
    //std::ostream&   operator<<(std::ostream&s, const Url& v)
    //{
        //return s << (UrlView) v;
    //}
    
    std::string     to_string(const Url&  u)
    {
        std::string     ret;
        stream::Text    txt(ret);
        txt << u;
        return ret;
    }
    
    std::string     to_string(const UrlView&u)
    {
        std::string     ret;
        stream::Text    txt(ret);
        txt << u;
        return ret;
    }
}
