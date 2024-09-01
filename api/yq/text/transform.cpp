////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "transform.hpp"
#include <yq/text/chars.hpp>
#include <yq/text/chars32.hpp>
#include <yq/text/copy.hpp>
#include <yq/text/counts.hpp>
#include <yq/text/format.hpp>
#include <yq/text/IgCase.hpp>
#include <yq/text/IterUtf8.hpp>

namespace yq {
    void    blank_cpp_comments(std::string& s)
    {
        const size_t kSize = s.size();
        for(size_t i=0;i<kSize;++i){
            if((s.at(i) == '/') && (s.at(i+1) == '/')){
                for(; (i<kSize) && (s.at(i) != '\n'); ++i)
                    s.at(i)   = ' ';
            }
        }
    }

    std::string  capitalize(const char*s, size_t n)
    {
        std::string ret;
        if(s && n){
            ret.reserve(n);
            bool        space = true;
            iter_utf8(s, n, [&](char32_t c){
                if(is_space(c)){
                    space   = true;
                    ret += c;
                } else {
                    if(is_alpha(c)){
                        if(space)
                            ret += to_upper(c);
                        else
                            ret += to_lower(c);
                    } else 
                        ret += c;
                    space   = false;
                }
            });
        }
        return ret;
    }
    
    std::string  capitalize(std::string_view s)
    {
        return capitalize(s.data(), s.size());
    }

    std::string concat(std::string_view a, std::string_view b)
    {
        std::string ret;
        ret.reserve(a.size()+b.size()+1);
        ret = a;
        ret += b;
        return ret;
    }

    std::vector<std::string_view>  hard_wrap(const char*s, size_t n, size_t width)
    {
        std::vector<std::string_view>   ret;
        const char*                     z = s;
        size_t                          i = 0;
        iter_utf8(s, n, [&](const char*p, char32_t){
            if(i >= width){
                ret.push_back(std::string_view(z, p));
                z   = p;
                i = 0;
            } else
                ++i;
        });
        if(i)
            ret.push_back(std::string_view(z, i));
        return ret;
    }
    
    std::vector<std::string_view>  hard_wrap(std::string_view s, size_t width)
    {
        return hard_wrap(s.data(), s.size(), width);
    }


    std::string     pad_left(std::string_view data, size_t minSize, char ch)
    {
        size_t  ccount  = count_characters(data);
        if(ccount >= minSize)
            return std::string(data);
        std::string ret(minSize-ccount, ch);
        ret += data;
        return ret;
    }
    
    std::string     pad_left(std::string_view data, size_t minSize, char32_t ch)
    {
        size_t  ccount  = count_characters(data);
        if(ccount >= minSize)
            return std::string(data);
            
        size_t  deficit = minSize - ccount;
        std::string bit = to_string(ch);
        std::string ret;
        ret.reserve(deficit * bit.size() + data.size());
        for(size_t i = 0; i<deficit; ++i)
            ret += bit;
        ret += data;
        return ret;
    }
    
    std::string  pad_right(std::string_view data, size_t minSize, char ch)
    {
        size_t  ccount  = count_characters(data);
        std::string ret = copy(data);
        if(ccount < minSize)
            ret.append(minSize-ccount, ch);
        return ret;
    }

    std::string  pad_right(std::string_view data, size_t minSize, char32_t ch)
    {
        size_t  ccount  = count_characters(data);
        if(ccount >= minSize)
            return std::string(data);
            
        size_t  deficit = minSize - ccount;
        std::string_view bit = to_string_view(ch);
        std::string ret;
        ret.reserve(deficit * bit.size() + data.size());
        ret += data;
        for(size_t i = 0; i<deficit; ++i)
            ret += bit;
        return ret;
    }

    std::string     pluralize(std::string_view sv)
    {
        if(sv.empty())
            return std::string(sv);
        std::string     ret;
        switch(sv[sv.size()-1]){
        case 's':
        case 'S':
            ret = sv;
            ret += "es";
            break;
        case 'y':
        case 'Y':
            if(sv.size() >= 2){
                ret += sv.substr(0,sv.size()-2);
                ret += "ies";
                break;
            }
            //[[fallthrough]]
        default:
            ret     += sv;
            ret += 's';
            break;
        }
        return ret;
    }

    size_t  replace_all(std::string& data, char what, char with)
    {
        size_t  cnt = 0;
        for(char& ch : data){
            if(ch == what){
                ch  = with;
                ++cnt;
            }
        }
        return cnt;
    }

    size_t  replace_all_igCase(std::string&data, char what, char with)
    {
        size_t  cnt = 0;
        what    = to_lower(what);
        for(char& ch : data){
            if(to_lower(ch) == what){
                ch  = with;
                ++cnt;
            }
        }
        return cnt;
    }

    
    std::string     simplify(const char*s, size_t n, char sp)
    { 
        bool            first   = true;
        bool            space   = true;
        std::string     ret;
        
        if(s && n){
            ret.reserve(n);
            iter_utf8(s, n, [&](const char* p, int len, char32_t ch){
                if(is_space(ch)){
                    space   = true;
                } else {
                    if(first){
                        first   = false;
                    } else if(space){
                        ret += sp;
                        space   = false;
                    }
                    ret.append(p, len);
                }
            });
        };
    
        return ret;
    }
    

    std::string     simplify(std::string_view sv, char sp)
    {
        return simplify(sv.data(), sv.size(), sp);
    }


    std::string_view    strip_extension(std::string_view name)
    {
        ssize_t  x   = (ssize_t) name.find_last_of('.');
        ssize_t  s   = (ssize_t) name.find_last_of('/');
        if(x > s+1)
            return name.substr(0,x);
        return name;
    }

    std::string  strip_spaces(const char* s, size_t n)
    {
        std::string  ret;
        ret.reserve(n);
        if(s && n){
            iter_utf8(s, n, [&](const char*p, int len, char32_t ch){
                if(len && !is_space(ch)){
                    ret.append(p, len);
                }
            });
        }
        return ret;
    }
    
    std::string  strip_spaces(std::string_view s)
    {
        return strip_spaces(s.data(), s.size());
    }



    std::string_view    trimmed(std::string_view sv)
    {
        if(sv.empty())
            return std::string_view();

        const char* s   = nullptr;
        const char* e   = nullptr;
        iter_utf8(sv, [&](const char* z, char32_t ch){
            if(!is_space(ch)){
                e   = z;
                if(!s)
                    s   = z;
            }
        });
        
        if(s && e){
            return std::string_view(s, e+1);
        } else
            return std::string_view();
    }
    
    std::string_view    trimmed(std::string_view sv, char c)
    {
        if(sv.empty())
            return std::string_view();
            
        const char* s   = nullptr;
        const char* e   = nullptr;
        for(s=sv.data(), e=sv.data()+sv.size(); (s<e) && (*s == c); ++s)
            ;
        for(; (s<e) && (e[-1] == c); --e)
            ;
        return std::string_view(s,e);
    }

    std::string_view    trimmed_end(std::string_view sv)
    {
        if(sv.empty())
            return std::string_view();

        const char* e   = nullptr;
        iter_utf8(sv, [&](const char* z, char32_t ch){
            if(!is_space(ch)){
                e   = z;
            }
        });
        
        if(e){
            return std::string_view(sv.data(), e+1);
        } else
            return std::string_view();
    }
    
    std::string_view    trimmed_end(std::string_view sv, char c)
    {
        if(sv.empty())
            return std::string_view();
            
        const char* s   = nullptr;
        const char* e   = nullptr;
        for(s=sv.data(), e=sv.data()+sv.size(); (s<e) && (e[-1] == c); --e)
            ;
        return std::string_view(s,e);
    }

    std::string_view    trimmed_start(std::string_view sv)
    {
        if(sv.empty())
            return std::string_view();

        const char* s   = nullptr;
        iter_utf8_abort(sv, [&](const char* z, char32_t ch) -> bool {
            if(!is_space(ch)){
                s   = z;
                return false;
            }
            return true;
        });
        if(s)
            return std::string_view(s, sv.data()+sv.size());
        return sv;
    }
    
    std::string_view    trimmed_start(std::string_view sv, char c)
    {
        if(sv.empty())
            return std::string_view();
            
        const char* s   = nullptr;
        const char* e   = nullptr;
        for(s=sv.data(), e=sv.data()+sv.size(); (s<e) && (*s == c); ++s)
            ;
        return std::string_view(s,e);
    }
    
}
