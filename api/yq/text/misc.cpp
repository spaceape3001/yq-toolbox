////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "misc.hpp"
#include <yq/container/MultiMap.hpp>
#include <yq/text/chars.hpp>
#include <yq/text/format.hpp>
#include <yq/text/parse.hpp>
#include <yq/text/IgCase.hpp>
#include <bitset>
#include <cuchar>

namespace yq {
    std::string&  operator+=(std::string&str, char32_t ch)
    {
        std::mbstate_t  state{};
        char            buffer[MB_CUR_MAX+1];
        int len = (int) c32rtomb(buffer, ch, &state);
        if(len > 0)
            str.append(buffer, len);
        return str;
    }

    std::string&    set_if_empty(std::string&a, std::string_view b, bool fOverride)
    {
        if((a.empty() || fOverride) && !b.empty())
            a  = b;
        return a;
    }

    namespace {
        std::bitset<256>    makeSet(const char* z)
        {
            std::bitset<256>    ret;
            for(;*z;++z)
                ret[*z] = true;
            return ret;
        }
        
    }

    std::string     web_decode(std::string_view sv)
    {
        std::string     ret;
        ret.reserve(sv.size());
        const char* end = sv.end();
        for(const char* c = sv.begin(); c<end; ++c){
            if(*c != '%'){
                ret += *c;
                continue;
            }

                    // tentatively accept it
            if((c+2<end) && is_xdigit(c[1]) && is_xdigit(c[2])){
                auto ch = to_hex(c+1,2);
                if(ch)
                    ret += (char) *ch;
            }
            
            // else assumed malformed, march  on
            c += 2;
        }
        return ret;
    }

    StringMultiMap  web_decode(StringViewMultiMap mm)
    {
        StringMultiMap  ret;
        for(auto& i : mm)
            ret.insert(web_decode(i.first), web_decode(i.second));
        return ret;
    }
    
    std::string     web_encode(std::string_view sv)
    {
        static const std::bitset<256>   good    = makeSet("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_.~");
        std::string     ret;
        ret.reserve(sv.size() * 3);
        for(char c : sv){
            if(good[c]){
                ret += c;
            } else {
                ret += '%';
                ret += fmt_hex((uint8_t) c, '0');
            }
        }
        return ret;
    }
}



    //  Need to keep this for future reference, though we'll need a less heap-destroying algorithm
    //QString         sanitize_path(const QString& path)
    //{
        //return sanitize_path(path.split('/')).join('/');
    //}

    //String          sanitize_path(const String& path)
    //{
        //return sanitize_path(path.qString());
    //}

    //QStringList     sanitize_path(const QStringList& path)
    //{
        //QStringList ret;
        //for(const QString& s : path){
            //if(s.isEmpty())
                //continue;
            //if(s == ".")
                //continue;
            //if(s == "..")
                //continue;
            //ret << s;
        //}
        //if(path.last().isEmpty())   // preserve the final empty for a "/"
            //ret << QString();
        //return ret;
    //}

