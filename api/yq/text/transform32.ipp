////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "transform32.hpp"
#include <yq/text/chars32.hpp>
#include <yq/text/copy32.hpp>
#include <yq/text/count32.hpp>
#include <yq/text/IgCase.hpp>

namespace yq {
    void    blank_cpp_comments(std::u32string& s)
    {
        const size_t kSize = s.size();
        for(size_t i=0;i<kSize;++i){
            if((s.at(i) == '/') && (s.at(i+1) == '/')){
                for(; (i<kSize) && (s.at(i) != '\n'); ++i)
                    s.at(i)   = ' ';
            }
        }
    }

    std::u32string  capitalize(const char32_t*s, size_t n)
    {
        std::u32string ret;
        if(s && n){
            ret.reserve(n);
            bool        space = true;
            for(size_t i=0;i<n;++n){
                if(is_space(s[i])){
                    space   = true;
                    ret += s[i];
                } else {
                    if(is_alpha(s[i])){
                        if(space)
                            ret += to_upper(s[i]);
                        else
                            ret += to_lower(s[i]);
                    } else 
                        ret += s[i];
                    space   = false;
                }
            }
        }
        return ret;
    }
    
    std::u32string  capitalize(std::u32string_view s)
    {
        return capitalize(s.data(), s.size());
    }

    std::u32string concat(std::u32string_view a, std::u32string_view b)
    {
        std::u32string ret;
        ret.reserve(a.size()+b.size()+1);
        ret = a;
        ret += b;
        return ret;
    }

    std::vector<std::u32string_view>  hard_wrap(const char32_t*s, size_t n, size_t width)
    {
        std::vector<std::u32string_view>   ret;
        size_t      cnt     = n / width;
        ret.reserve(cnt+1);
        for(size_t j=0;j<cnt;++j){
            ret.push_back(std::u32string_view(s + j*width, width));
        }
        size_t j = n % width;
        if(j){
            ret.push_back(std::u32string_view(s + cnt*width, j));
        }
        return ret;
    }
    
    std::vector<std::u32string_view>  hard_wrap(std::u32string_view s, size_t width)
    {
        return hard_wrap(s.data(), s.size(), width);
    }

    std::u32string     pad_left(std::u32string_view data, size_t minSize, char32_t ch)
    {
        size_t  ccount  = count_characters(data);
        if(ccount >= minSize)
            return std::u32string(data);
        std::u32string ret(minSize-ccount, ch);
        ret += data;
        return ret;
    }
    
    std::u32string  pad_right(std::u32string_view data, size_t minSize, char32_t ch)
    {
        size_t  ccount  = count_characters(data);
        std::u32string ret = copy(data);
        if(ccount < minSize)
            ret.append(minSize-ccount, ch);
        return ret;
    }

    std::u32string     pluralize(std::u32string_view sv)
    {
        if(sv.empty())
            return std::u32string(sv);
        std::u32string     ret;
        switch(sv[sv.size()-1]){
        case 's':
        case 'S':
            ret = sv;
            ret += U"es";
            break;
        case 'y':
        case 'Y':
            if(sv.size() >= 2){
                ret += sv.substr(0,sv.size()-2);
                ret += U"ies";
                break;
            }
            //[[fallthrough]]
        default:
            ret     += sv;
            ret += U's';
            break;
        }
        return ret;
    }

    size_t  replace_all(std::u32string& data, char32_t what, char32_t with)
    {
        size_t  cnt = 0;
        for(char32_t& ch : data){
            if(ch == what){
                ch  = with;
                ++cnt;
            }
        }
        return cnt;
    }

    size_t  replace_all_igCase(std::u32string&data, char32_t what, char32_t with)
    {
        size_t  cnt = 0;
        what    = to_lower(what);
        for(char32_t& ch : data){
            if(to_lower(ch) == what){
                ch  = with;
                ++cnt;
            }
        }
        return cnt;
    }

    std::u32string     simplify(const char32_t*s, size_t n, char32_t sp)
    { 
        bool                first   = true;
        bool                space   = true;
        std::u32string     ret;
        
        if(s && n){
            ret.reserve(n);
            for(size_t i=0;i<n;++i){
                if(is_space(s[i])){
                    space   = true;
                } else {
                    if(first){
                        first   = false;
                    } else if(space){
                        ret.push_back(sp);
                        space   = false;
                    }
                    ret.push_back(s[i]);
                }
            }
        };
    
        return ret;
    }
    

    std::u32string     simplify(std::u32string_view sv, char32_t sp)
    {
        return simplify(sv.data(), sv.size(), sp);
    }


    std::u32string_view    strip_extension(std::u32string_view name)
    {
        ssize_t  x   = (ssize_t) name.find_last_of('.');
        ssize_t  s   = (ssize_t) name.find_last_of('/');
        if(x > s+1)
            return name.substr(0,x);
        return name;
    }

    std::u32string  strip_spaces(const char32_t* s, size_t n)
    {
        std::u32string  ret;
        ret.reserve(n);
        if(s && n){
            for(size_t i=0;i<n;++i){
                if(!is_space(s[i])){
                    ret += s[i];
                }
            }
        }
        return ret;
    }
    
    std::u32string  strip_spaces(std::u32string_view s)
    {
        return strip_spaces(s.data(), s.size());
    }


    std::u32string_view    trimmed(std::u32string_view sv)
    {
        if(sv.empty())
            return std::u32string_view();

        const char32_t* s   = nullptr;
        const char32_t* e   = nullptr;
        
        for(size_t i=0;i<sv.size();++i){
            char32_t    ch  = sv[i];
            if(!is_space(ch)){
                e   = &sv[i];
                if(!s)
                    s   = &sv[i];
            }
        }
        
        if(s && e){
            return std::u32string_view(s, e+1);
        } else
            return std::u32string_view();
    }
    
    std::u32string_view    trimmed(std::u32string_view sv, char32_t c)
    {
        if(sv.empty())
            return std::u32string_view();
            
        const char32_t* s   = nullptr;
        const char32_t* e   = nullptr;
        for(s=sv.data(), e=sv.data()+sv.size(); (s<e) && (*s == c); ++s)
            ;
        for(; (s<e) && (e[-1] == c); --e)
            ;
        return std::u32string_view(s,e);
    }

    std::u32string_view    trimmed_end(std::u32string_view sv)
    {
        if(sv.empty())
            return std::u32string_view();

        const char32_t* e   = nullptr;
        for(size_t i=0;i<sv.size();++i){
            char32_t    ch  = sv[i];
            if(!is_space(ch)){
                e   = &sv[i];
            }
        }
        
        if(e){
            return std::u32string_view(sv.data(), e+1);
        } else
            return std::u32string_view();
    }
    
    std::u32string_view    trimmed_end(std::u32string_view sv, char32_t c)
    {
        if(sv.empty())
            return std::u32string_view();
            
        const char32_t* s   = nullptr;
        const char32_t* e   = nullptr;
        for(s=sv.data(), e=sv.data()+sv.size(); (s<e) && (e[-1] == c); --e)
            ;
        return std::u32string_view(s,e);
    }

    std::u32string_view    trimmed_start(std::u32string_view sv)
    {
        if(sv.empty())
            return std::u32string_view();

        const char32_t* s   = nullptr;
        for(size_t i=0;i<sv.size();++i){
            if(!is_space(sv[i])){
                s   = &sv[i];
                break;
            }
        }
        if(s)
            return std::u32string_view(s, sv.data()+sv.size());
        return sv;
    }
    
    std::u32string_view    trimmed_start(std::u32string_view sv, char32_t c)
    {
        if(sv.empty())
            return std::u32string_view();
            
        const char32_t* s   = nullptr;
        const char32_t* e   = nullptr;
        for(s=sv.data(), e=sv.data()+sv.size(); (s<e) && (*s == c); ++s)
            ;
        return std::u32string_view(s,e);
    }
}
