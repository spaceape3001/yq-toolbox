////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/text/split.hpp>
#include <yq/text/vsplit.hpp>
#include <yq/text/IterUtf8.hpp>
#include <yq/text/chars32.hpp>

namespace yq {

    std::vector<std::string_view>  split(const char* s, size_t n, size_t num)
    {
        std::vector<std::string_view>    ret;
        if(s && n){
            if(!num)
                ++num;
                
            ret.reserve(num);
            size_t  j0  =  0;
            size_t  j1;
            
            for(size_t i = 0; i<num; j0=j1, ++i){
                j1  = std::min(((i+1)*n)/num, n);
                ret.push_back(std::string_view(s+j0, j1-j0));
            }
        }
        return ret;
    }

    std::vector<std::string_view>  split(std::string_view s, size_t number)
    {
        return split(s.data(), s.size(), number);
    }

    std::vector<std::string_view>  split(const char*s, size_t n, char ch)
    {
        std::vector<std::string_view>  ret;
        vsplit(s, n, ch, [&](std::string_view token){
            ret.push_back(token);
        });
        return ret;
    }

    std::vector<std::string_view>  split(std::string_view s, char ch)
    {
        return split(s.data(), s.size(), ch);
    }

    std::vector<std::string_view>  split(const char* s, size_t n, char ch, size_t number)
    {
        std::vector<std::string_view>  ret;
        if(s && n){
            const char* end = s + n;
            const char* i   = nullptr;
            const char* j   = nullptr;
            if(number){
                for(i = s; (j = strnchr(i, end-i, ch)) && --number; i = j)
                    ret.push_back(std::string_view(i, j-i));
            }
            ret.push_back(std::string_view(i, end-i));
        }
        return ret;
    }

    std::vector<std::string_view>  split(std::string_view s, char ch, size_t number)
    {
        return split(s.data(), s.size(), ch, number);
    }

    std::vector<std::string_view>  split(const char* s, size_t n, char32_t ch)
    {
        std::vector<std::string_view>    ret;
        if(s && n){
            const char*     z0  = s;
            iter_utf8(s, n, [&](const char*z, char32_t wc){
                if(wc == ch){
                    ret.push_back(std::string_view(z0, z));
                    z0      = z;
                }
            });
            ret.push_back(std::string_view(z0, s+n));
        }
        return ret;
    }

    std::vector<std::string_view>  split(std::string_view s, char32_t ch)
    {
        return split(s.data(), s.size(), ch);
    }
    
    std::vector<std::string_view>  split(const char* s, size_t n, char32_t ch, size_t number)
    {
        std::vector<std::string_view>    ret;
        if(s && n){
            const char*     z0  = s;
            if(number){
                iter_utf8(s, n, [&](const char*z, char32_t wc){
                    if(wc == ch){
                        if(--number){
                            ret.push_back(std::string_view(z0, z));
                            z0      = z;
                        }
                    }
                });
            }
            ret.push_back(std::string_view(z0, s+n));
        }
        return ret;
    }
    
    std::vector<std::string_view>  split(std::string_view s, char32_t ch, size_t number)
    {
        return split(s.data(), s.size(), ch, number);
    }

    std::vector<std::string_view>  split(const char* s, size_t n, const char* p, size_t pn)
    {
        std::vector<std::string_view>  ret;
        vsplit(s, n, p, pn, [&](std::string_view token){
            ret.push_back(token);
        });
        return ret;
    }
    
    std::vector<std::string_view>  split(std::string_view s, std::string_view p)
    {
        return split(s.data(), s.size(), p.data(), p.size());
    }

    std::vector<std::string_view>  split_igCase(const char* s , size_t n, char ch)
    {
        std::vector<std::string_view>  ret;
        vsplit_igCase(s, n, ch, [&](std::string_view token){
            ret.push_back(token);
        });
        return ret;
    }
    
    std::vector<std::string_view>  split_igCase(std::string_view s, char ch)
    {
        return split_igCase(s.data(), s.size(), ch);
    }

    std::vector<std::string_view>  split_igCase(const char* s, size_t n, char32_t ch)
    {
        std::vector<std::string_view>    ret;
        if(s && n){
            ch = to_lower(ch);
            const char*     z0  = s;
            iter_utf8(s, n, [&](const char*z, char32_t wc){
                if(to_lower(wc) == ch){
                    ret.push_back(std::string_view(z0, z));
                    z0      = z;
                }
            });
            ret.push_back(std::string_view(z0, s+n));
        }
        return ret;
    }
    
    std::vector<std::string_view>  split_igCase(std::string_view s, char32_t ch)
    {
        return split_igCase(s.data(), s.size(), ch);
    }
    
    std::vector<std::string_view>  split_igCase(const char* s, size_t n, const char*p, size_t pn)
    {
        std::vector<std::string_view>  ret;
        vsplit_igCase(s, n, p, pn, [&](std::string_view token){
            ret.push_back(token);
        });
        return ret;
    }
    
    std::vector<std::string_view>  split_igCase(std::string_view s, std::string_view p)
    {
        return split_igCase(s.data(), s.size(), p.data(), p.size());
    }
}
