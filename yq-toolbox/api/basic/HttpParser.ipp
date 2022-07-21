////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <basic/HttpParser.hpp>
#include <basic/MultiMap.hpp>
#include <basic/TextUtils.hpp>

namespace yq {
    StringViewMultiMap     parse_cookie(std::string_view cs)
    {
        StringViewMultiMap ret;
        vsplit(cs, ';', [&](std::string_view s){
            const char* eq  = strnchr(s, '=');
            if(eq){
                std::string_view k   = trimmed(std::string_view(s.data(), eq));
                std::string_view v   = trimmed(std::string_view(eq+1, s.end()));
                ret.insert(k, v);
            } else {
                ret.insert(trimmed(s), std::string_view());
            }
        });
        return ret;
    }
    
    KVView                  parse_header_line(std::string_view s)
    {
        KVView          ret;
        const char* c   = strnchr(s, ':');
        if(c){
            ret.key     = trimmed(std::string_view(s.data(), c));
            ret.value   = trimmed(std::string_view(c+1, s.end()));
        }
        return ret;
    }



    MethodUriVersion        parse_method_uri(std::string_view input)
    {
        const char* z       = nullptr;
        const char* str     = nullptr;
        
        enum Mode {
            Start    = 0,
            Method,
            MSpace,
            Uri,
            USpace,
            Version,
            Done
        };
        
        Mode                mode    = Start;
        MethodUriVersion    ret;

        for(z = input.begin(); z<input.end(); ++z){
            switch(mode){
            case Start:
                if(!is_space(*z)){
                    str     = z;
                    mode    = Method;
                }
                break;
            case Method:
                if(is_space(*z)){
                    ret.method  = std::string_view(str, z);
                    mode    = MSpace;
                }
                break;
            case MSpace:
                if(is_space(*z))
                    break;
                str     = z;
                mode    = Uri;
                break;
            case Uri:
                if(is_space(*z)){
                    ret.uri = std::string_view(str, z);
                    mode    = USpace;
                }
                break;
            case USpace:
                if(is_space(*z))
                    break;
                str = z;
                mode    = Version;
                break;
            case Version:
                if(is_space(*z)){
                    ret.version = std::string_view(str, z);
                    mode        = Done;
                }
                break;
            default:
                break;
            }
        }
        
        switch(mode){
        case Method:
            ret.method  = std::string_view(str, z);
            break;
        case Uri:
            ret.uri = std::string_view(str, z);
            break;
        case Version:
            ret.version  = std::string_view(str, z);
            break;
        default:
            break;
        }
        
        return ret;
    }
    

    StringViewMultiMap parse_parameters(std::string_view sv)
    {
        StringViewMultiMap  ret;
        if(!sv.empty()){
            vsplit(sv, '&', [&](std::string_view b){
                const char* eq  = strnchr(b, '=');
                if(!eq)
                    return;
                ret.insert(std::string_view(b.data(), eq), std::string_view(eq+1, b.end()));
            });
        }
        return ret;
    }

    QueryStripped           stripped_query(std::string_view key, std::string_view query, bool first)
    {
        QueryStripped   ret;
        ret.rest.reserve(query.size());
        
        vsplit(query, '&', [&](std::string_view b){
            const char* eq  = strnchr(b, '=');
            if(eq && is_similar(std::string_view(b.data(), eq), key)){
                if(ret.value.empty() || !first)
                    ret.value   = web_decode(std::string_view(eq+1, b.end()));
            } else {
                if(!ret.rest.empty())
                    ret.rest += '&';
                ret.rest += b;
            }
        });
        return ret;
    }
    
}

