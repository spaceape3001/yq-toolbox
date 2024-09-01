////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

//#pragma once

#include <0/basic/TextUtils.hpp>

#include <0/basic/Compare.hpp>
#include <yq/text/Comma.hpp>
#include <yq/text/IterUtf8.hpp>
#include <yq/text/Iter32.hpp>
#include <yq/text/IterW.hpp>
#include <yq/container/List.hpp>
#include <yq/container/Map.hpp>
#include <yq/container/MultiMap.hpp>
#include <yq/basic/Result.hpp>
#include <yq/container/Set.hpp>
#include <0/basic/TextUtils32.hpp>

#include <bitset>

    /*
        GCC v10 did not support to/from chars on floating point types.  It's been enabled in v11.
        Therefore, we'll macro this portion. :(
    */
#if defined(MSVC)
    #define FP_CHARCONV 1
#elif defined(__GNUC__)
    #if __GNUC__ >= 11
        #define FP_CHARCONV 1
    #endif
#endif
#ifndef FP_CHARCONV
    #define FP_CHARCONV 0
#endif

namespace yq {

    //! Trims a string's leading/trailing whitespace by altering parameters
    void    trim_ws(const char*& s, size_t& n);
    
    namespace {
        //! Standard  buffer size for formatting numbers and the like
        static constexpr const size_t   kStdTextBuf = 63;
        
        
        //const char* nonspace(const char* s, size_t n)
        //{
            //while(s && *s && isspace(*s) && n)
                //++s, --n;
            //return s;
        //}

        //! Checks for equality by assuming left may vary in case, the right will be lower case.
        bool    is_same(const char*a, size_t n, const char *b)
        {
            if(a && b){
                for(;*a && *b && n; ++a, ++b, --n){
                    if(::tolower(*a) != *b)
                        return false;
                }
                return !(*b || n);
            }
            return false;
        }
        
        
        static constexpr const auto fFAIL     = float_r(false, NaNf);
        

        
        std::string     cvt_u32string(const char32_t *z, size_t n)
        {
            std::string ret;
            ret.resize((std::max<size_t>(64, n*4)));    // approx guess
            std::mbstate_t  state{};
            size_t          m   = 0;
            for(size_t i=0;i<n;++i){
                if(ret.size() - m < 6)
                    ret.resize(ret.size() * 2);
                m += c32rtomb(ret.data()+m, z[i], &state);
            }
            ret.resize(m);
            return ret;
        }
        
        std::string     cvt_wstring(const wchar_t *z, size_t n)
        {
            std::string ret;
            ret.resize((std::max<size_t>(64, n*4)));    // approx guess
            std::mbstate_t  state{};
            size_t          m   = 0;
            for(size_t i=0;i<n;++i){
                if(ret.size() - m < 6)
                    ret.resize(ret.size() * 2);
                m += wcrtomb(ret.data()+m, z[i], &state);
            }
            ret.resize(m);
            return ret;
        }
        //  IF ever needed for wchar_t, rename "c32rtomb" to "wcrtomb".
        
    }


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

    Compare compare(std::string_view a, std::string_view b)
    {
        size_t  c   = std::min(a.size(), b.size());
        for(size_t i=0;i<c;++i){
            if(a[i] < b[i])
                return Compare::LESSER;
            if(a[i] > b[i])
                return Compare::GREATER;
        }
        
        return compare(a.size(), b.size());
    }

    Compare compare_igCase(std::string_view sa, std::string_view sb)
    {
        IterUtf8  a(sa);
        IterUtf8  b(sb);
        
        for(;;){
            char32_t  ca  = a.next();
            char32_t  cb  = b.next();
            
            int64_t n   = (int64_t) to_lower(ca) - (int64_t) to_lower(cb);
            if(n<0)
                return Compare::LESSER;
            else if(n>0)
                return Compare::GREATER;
            if(!ca)
                return Compare::EQUAL;
        }
    }

    std::string concat(std::string_view a, std::string_view b)
    {
        std::string ret;
        ret.reserve(a.size()+b.size()+1);
        ret = a;
        ret += b;
        return ret;
    }

    bool    contains(const char* haystack, size_t nHaystack, const char* needle, size_t nNeedle)
    {
        return strnstr(haystack, nHaystack, needle, nNeedle) ? true : false;
    }

    bool    contains(std::string_view haystack, std::string_view needle)
    {
        return contains(haystack.data(), haystack.size(), needle.data(), needle.size());
    }

    bool    contains_igCase(const char* haystack, size_t nHaystack, const char* needle, size_t nNeedle)
    {
        return strnstr_igCase(haystack, nHaystack, needle, nNeedle) ? true : false;
    }

    bool    contains_igCase(std::string_view haystack, std::string_view needle)
    {
        return contains_igCase(haystack.data(), haystack.size(), needle.data(), needle.size());
    }

    string_set_t        copy(const string_view_set_t&input)
    {
        string_set_t    ret;
        for(auto& s : input)
            ret.insert(copy(s));
        return ret;
    }

    std::vector<std::string>    copy(const std::vector<std::string>&input)
    {
        std::vector<std::string>    ret;
        ret.reserve(input.size());
        for(const std::string& s : input)
            ret.push_back(s);
        return ret;
    }
    
    std::vector<std::string>    copy(const std::vector<std::string_view>&input)
    {
        std::vector<std::string>    ret;
        ret.reserve(input.size());
        for(std::string_view s : input)
            ret.push_back(std::string(s));
        return ret;
    }

    std::vector<std::string>  copy(std::initializer_list<std::string_view> input)
    {
        std::vector<std::string>    ret;
        ret.reserve(input.size());
        for(std::string_view s : input)
            ret.push_back(std::string(s));
        return ret;
    }

    size_t  count_characters(const char* s, size_t n)
    {
        size_t  ret = 0;
        if(s && n){
            iter_utf8(s, n, [&](char32_t){ ++ret; });
        }
        return ret;
    }
    
    size_t  count_characters(std::string_view s)
    {
        return count_characters(s.data(), s.size());
    }
    
    size_t  count_characters(const char* s, size_t n, char ch)
    {
        size_t ret =0;
        if(s && n){
            for(size_t i=0;i<n;++i)
                if(s[i] == ch)
                    ++ret;
        }
        return ret;
    }
    
    size_t  count_characters(std::string_view s, char ch)
    {
        return count_characters(s.data(), s.size(), ch);
    }
    
    size_t  count_characters(const char* s, size_t n, char32_t ch)
    {
        size_t ret=0;
        if(s && n){
            iter_utf8(s, n, [&](char32_t c){ 
                if(c == ch) 
                    ++ret; 
            });
        }
        return ret;
    }
    
    size_t  count_characters(std::string_view s, char32_t ch)
    {
        return count_characters(s.data(), s.size(), ch);
    }


    size_t  count_characters_igCase(const char* s, size_t n, char ch)
    {
        size_t  ret = 0;
        if(s && n){
            ch  = to_lower(ch);
            for(size_t i=0;i<n;++i){
                if(to_lower(s[i]) == ch)
                    ++ ret;
            }
        }
        return ret;
    }
    

    size_t  count_characters_igCase(std::string_view s, char ch)
    {
        return count_characters_igCase(s.data(), s.size(), ch);
    }
    
    size_t  count_characters_igCase(const char* s, size_t n, char32_t ch)
    {
        size_t  ret = 0;
        if(s && n){
            ch  = to_lower(ch);
            iter_utf8(s, n, [&](char32_t c){
                if(to_lower(c) == ch)
                    ++ret;
            });
        }
        return ret;
    }
    
    size_t  count_characters_igCase(std::string_view s, char32_t ch)
    {
        return count_characters_igCase(s.data(), s.size(), ch);
    }

    size_t  count_start_spaces(std::string_view a)
    {
        size_t  ret   = 0;
        iter_utf8_abort(a, [&](char32_t ch) -> bool {
            if(is_space(ch)){
                ++ret;
                return true;
            } else
                return false;
        });
        return ret;
    }

    
    size_t  count_starts(std::string_view s, char ch)
    {
        size_t  n = 0;
        for(; (n<s.size()) && (s[n] == ch); ++n)
            ;
        return n;
    }

    bool    ends(std::string_view hay, std::string_view pat)
    {
        if(pat.size() > hay.size())
            return false;
        return hay.substr(hay.size()-pat.size()) == pat;
    }

    char32_t  first_non_blank_char(std::string_view a)
    {
        char32_t  ret   = 0;
        iter_utf8_abort(a, [&](char32_t ch) -> bool {
            if(!is_space(ch)){
                ret = ch;
                return false;
            }
            return true;
        });
        return ret;
    }

    std::string_view  first_non_empty(std::string_view a, std::string_view b)
    {
        return a.empty() ? b : a;
    }

    std::string_view  first_non_empty(std::string_view a, std::string_view b, std::string_view c)
    {
        if(!a.empty())
            return a;
        if(!b.empty())
            return b;
        return c;
    }

    std::string_view  first_non_empty(std::string_view a, std::string_view b, std::string_view c, std::string_view d)
    {
        if(!a.empty())
            return a;
        if(!b.empty())
            return b;
        if(!c.empty())
            return c;
        return d;
    }

    std::string_view  first_non_empty(std::initializer_list<std::string_view> args)
    {
        for(std::string_view s : args)
            if(!s.empty())
                return s;
        return std::string_view();
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


    bool  is_equal(std::string_view a, std::string_view b)
    {
        return is_equal(compare(a,b));
    }

    bool  is_greater_igCase(std::string_view a, std::string_view b)
    {
        return is_greater(compare_igCase(a,b));
    }

    bool  is_in(std::string_view str, std::string_view pat)
    {
        return is_similar(str, pat);
    }
    

    bool  is_in(std::string_view str, std::initializer_list<std::string_view> pat)
    {
        for(auto& s : pat)
            if(is_similar(str, s))
                return true;
        return false;
    }
    
    bool  is_in(std::string_view str, const string_view_set_t& pat)
    {
        return pat.contains(str);
    }

    bool  is_in(std::string_view str, const std::vector<std::string_view>& pat)
    {
        for(auto& s : pat)
            if(is_similar(str, s))
                return true;
        return false;
    }

    bool  is_in(char32_t ch, std::string_view pat)
    {
        Iter32 them(pat);
        while(them.more()){
            if(is_similar(them.next(), ch))
                return true;
        }
        return false;
    }

    bool  is_less_igCase(std::string_view a, std::string_view b)
    {
        return is_less( compare_igCase(a,b));
    }

    bool  is_less_igCase_u8(std::string_view a, std::string_view b)
    {
        return is_less( compare_igCase(a,b));
    }

    bool  is_similar(char a, char b)
    {
        return to_lower(a) == to_lower(b);
    }

    bool  is_similar(std::string_view a, std::string_view b)
    {
        if(a.size() != b.size())
            return false;
        return is_equal( compare_igCase(a, b));
    }


    bool        is_valid_key(std::string_view k)
    {
        if(k.empty())
            return false;
        
        if(!is_alnum(k[0]))
            return false;
        for(size_t i=1;i<k.size();++i){
            if(is_alnum(k[i]))
                continue;
            switch(k[i]){
            case '-':
            case '_':
            case '+':
                continue;
            default:
                return false;
            }
        }
        return true;
    }

    bool        matches_at(std::string_view haystack, size_t pos, std::string_view pattern)
    {
        return starts(haystack.substr(pos), pattern);
    }
    
    bool        matches_at_igCase(std::string_view haystack, size_t pos, std::string_view pattern)
    {
        return starts_igCase(haystack.substr(pos), pattern);
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

    std::string&    set_if_empty(std::string&a, std::string_view b, bool fOverride)
    {
        if((a.empty() || fOverride) && !b.empty())
            a  = b;
        return a;
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

    
    Expect<bool>  to_boolean(const char*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s, n);
        if(!n)
            return errors::empty_string();
        switch(*s){
        case '0':
            if(is_same(s,n,"0"))
                return false;
            break;
        case '1':
            if(is_same(s, n, "1"))
                return true;
            break;
        case 'y':
        case 'Y':
            if(n == 1)
                return true;
            if(is_same(s, n, "yes"))
                return true;
            break;
        case 'n':
        case 'N':
            if(n == 1)
                return false;
            if(is_same(s, n, "no"))
                return false;
            break;
        case 't':
        case 'T':
            if(n == 1)
                return true;
            if(is_same(s, n, "true"))
                return true;
            break;
        case 'f':
        case 'F':
            if(n==1)
                return false;
            if(is_same(s, n, "false"))
                return false;
            break;
        default:
            break;
        }
        
        return errors::bad_argument();
    }

    Expect<bool> to_boolean(std::string_view s)
    {
        return to_boolean(s.data(), s.size());
    }

    Expect<double>  to_double(const char*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();

        trim_ws(s, n);
        switch(n){
        case 0:
            return 0.;
        case 3:
            if(strncasecmp(s, "nan", 3) == 0)
                return NaN;
            if(strncasecmp(s, "inf", 3) == 0)
                return INF;
            break;
        }
        

        double  result = NaN;
        auto [p,ec] = std::from_chars(s, s+n, result, std::chars_format::general);
        if(ec != std::errc())
            return std::unexpected(std::make_error_code(ec));
        return result;
    }

    Expect<double>  to_double(std::string_view s)
    {
        return to_double(s.data(), s.size());
    }

    Expect<float>  to_float(const char*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();

        trim_ws(s, n);

        switch(n){
        case 0:
            return 0.f;
        case 3:
            if(strncasecmp(s, "nan", 3) == 0)
                return NaNf;
            if(strncasecmp(s, "inf", 3) == 0)
                return INFf;
            break;
        }
        
        float  result = NaNf;
        auto [p,ec] = std::from_chars(s, s+n, result, std::chars_format::general);
        if(ec != std::errc())
            return std::unexpected(std::make_error_code(ec));
        return result;
    }

    Expect<float>  to_float(std::string_view s)
    {
        return to_float(s.data(), s.size());
    }



    std::string   to_string(const char32_t*z)
    {
        if(!z)
            return std::string();
        return cvt_u32string(z, strnlen(z, kMaxNullTermString));
    }

    std::string to_string(const std::u32string&s)
    {
        return cvt_u32string(s.data(), s.size());
    }
    

    std::string to_string(const std::u32string_view&s)
    {
        return cvt_u32string(s.data(), s.size());
    }

    std::string to_string(const std::wstring&s)
    {
        return cvt_wstring(s.data(), s.size());
    }


    std::string to_string(const std::wstring_view&s)
    {
        return cvt_wstring(s.data(), s.size());
    }


    std::string_view  to_string_view(const std::u8string_view&s)
    {
        return std::string_view((const char*) s.data(), s.size());
    }

    string_view_set_t  to_string_view_set(const string_set_t& vals)
    {
        string_view_set_t  ret;
        for(const std::string& v : vals)
            ret.insert(v);
        return ret;
    }

    std::u32string      to_u32string(std::string_view in)
    {
        std::u32string      ret;
        Iter32  input(in);
        while(input.more())
            ret.push_back(input.next());
        return ret;
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

 
