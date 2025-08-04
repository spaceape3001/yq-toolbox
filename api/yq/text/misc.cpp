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
    uint8_t         digits(uint8_t v)
    {
        if(v<10)
            return 1;
        if(v<100)
            return 2;
        return 3;
    }

    uint8_t         digits(uint16_t v)
    {
        if(v<10)
            return 1;
        if(v<100)
            return 2;
        if(v<1'000)
            return 3;
        if(v<10'000)
            return 4;
        return 5;
    }

    uint8_t         digits(uint32_t v)
    {
        if(v<10UL)
            return 1;
        if(v<100UL)
            return 2;
        if(v<1'000UL)
            return 3;
        if(v<10'000UL)
            return 4;
        if(v<100'000UL)
            return 5;
        if(v<1'000'000UL)
            return 6;
        if(v<10'000'000UL)
            return 7;
        if(v<100'000'000UL)
            return 8;
        if(v<1'000'000'000UL)
            return 9;
        return 10;
    }

    uint8_t         digits(uint64_t v)
    {
        if(v<10ULL)
            return 1;
        if(v<100ULL)
            return 2;
        if(v<1'000ULL)
            return 3;
        if(v<10'000ULL)
            return 4;
        if(v<100'000ULL)
            return 5;
        if(v<1'000'000ULL)
            return 6;
        if(v<10'000'000ULL)
            return 7;
        if(v<100'000'000ULL)
            return 8;
        if(v<1'000'000'000ULL)
            return 9;
        if(v<10'000'000'000ULL)
            return 10;
        if(v<100'000'000'000ULL)
            return 11;
        if(v<1'000'000'000'000ULL)
            return 12;
        if(v<10'000'000'000'000ULL)
            return 13;
        if(v<100'000'000'000'000ULL)
            return 14;
        if(v<1'000'000'000'000'000ULL)
            return 15;
        if(v<10'000'000'000'000'000ULL)
            return 16;
        if(v<100'000'000'000'000'000ULL)
            return 17;
        if(v<1'000'000'000'000'000'000ULL)
            return 18;
        if(v<10'000'000'000'000'000'000ULL)
            return 19;
        return 20;
    }

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

