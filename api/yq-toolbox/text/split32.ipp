////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq-toolbox/text/split32.hpp>
#include <yq-toolbox/text/vsplit32.hpp>

namespace yq {

    std::vector<std::u32string_view>  split(const char32_t* s, size_t n, size_t num)
    {
        std::vector<std::u32string_view>    ret;
        if(s && n){
            if(!num)
                ++num;
                
            ret.reserve(num);
            size_t  j0  =  0;
            size_t  j1;
            
            for(size_t i = 0; i<num; j0=j1, ++i){
                j1  = std::min(((i+1)*n)/num, n);
                ret.push_back(std::u32string_view(s+j0, j1-j0));
            }
        }
        return ret;
    }

    std::vector<std::u32string_view>  split(std::u32string_view s, size_t number)
    {
        return split(s.data(), s.size(), number);
    }

    std::vector<std::u32string_view>  split(const char32_t*s, size_t n, char32_t ch)
    {
        std::vector<std::u32string_view>  ret;
        vsplit(s, n, ch, [&](std::u32string_view token){
            ret.push_back(token);
        });
        return ret;
    }

    std::vector<std::u32string_view>  split(std::u32string_view s, char32_t ch)
    {
        return split(s.data(), s.size(), ch);
    }

    std::vector<std::u32string_view>  split(const char32_t* s, size_t n, char32_t ch, size_t number)
    {
        std::vector<std::u32string_view>  ret;
        if(s && n){
            const char32_t* end = s + n;
            const char32_t* i   = nullptr;
            const char32_t* j   = nullptr;
            if(number){
                for(i = s; (j = strnchr(i, end-i, ch)) && --number; i = j)
                    ret.push_back(std::u32string_view(i, j-i));
            }
            ret.push_back(std::u32string_view(i, end-i));
        }
        return ret;
    }

    std::vector<std::u32string_view>  split(std::u32string_view s, char32_t ch, size_t number)
    {
        return split(s.data(), s.size(), ch, number);
    }

    std::vector<std::u32string_view>  split(const char32_t* s, size_t n, const char32_t* p, size_t pn)
    {
        std::vector<std::u32string_view>  ret;
        vsplit(s, n, p, pn, [&](std::u32string_view token){
            ret.push_back(token);
        });
        return ret;
    }
    
    std::vector<std::u32string_view>  split(std::u32string_view s, std::u32string_view p)
    {
        return split(s.data(), s.size(), p.data(), p.size());
    }

    std::vector<std::u32string_view>  split_igCase(const char32_t* s , size_t n, char32_t ch)
    {
        std::vector<std::u32string_view>  ret;
        vsplit_igCase(s, n, ch, [&](std::u32string_view token){
            ret.push_back(token);
        });
        return ret;
    }
    
    std::vector<std::u32string_view>  split_igCase(std::u32string_view s, char32_t ch)
    {
        return split_igCase(s.data(), s.size(), ch);
    }
    
    std::vector<std::u32string_view>  split_igCase(const char32_t* s, size_t n, const char32_t*p, size_t pn)
    {
        std::vector<std::u32string_view>  ret;
        vsplit_igCase(s, n, p, pn, [&](std::u32string_view token){
            ret.push_back(token);
        });
        return ret;
    }
    
    std::vector<std::u32string_view>  split_igCase(std::u32string_view s, std::u32string_view p)
    {
        return split_igCase(s.data(), s.size(), p.data(), p.size());
    }
}
