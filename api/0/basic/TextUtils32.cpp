////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <0/basic/TextUtils32.hpp>

#include <0/basic/Compare.hpp>
#include <yq/text/Comma.hpp>
#include <yq/text/IterUtf8.hpp>
#include <yq/text/Iter32.hpp>
#include <yq/text/IterW.hpp>
#include <yq/container//List.hpp>
#include <yq/container/Map.hpp>
#include <yq/container/MultiMap.hpp>
#include <yq/container/Set.hpp>
#include <0/basic/TextUtils.hpp>

#include <bitset>

    /*
        GCC v10 did not support to/from char32_ts on floating point types.  It's been enabled in v11.
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

    void    trim_ws(const char32_t*& s, size_t& n);
    
    namespace {
        //! Standard  buffer size for formatting numbers and the like
        static constexpr const size_t   kStdTextBuf = 63;

        
        //const char32_t* nonspace(const char32_t* s, size_t n)
        //{
            //while(s && *s && isspace(*s) && n)
                //++s, --n;
            //return s;
        //}

        //! Checks for equality by assuming left may vary in case, the right will be lower case.
        bool    is_same(const char32_t*a, size_t n, const char32_t *b)
        {
            if(a && b){
                for(;*a && *b && n; ++a, ++b, --n){
                    if(to_lower(*a) != *b)
                        return false;
                }
                return !(*b || n);
            }
            return false;
        }
        
        
//        static constexpr const auto fFAIL     = float_r(false, NaNf);

        //  IF ever needed for wchar32_t_t, rename "c32rtomb" to "wcrtomb".
        

    }

    
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

    Compare compare(std::u32string_view a, std::u32string_view b)
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

    Compare compare_igCase(std::u32string_view sa, std::u32string_view sb)
    {
        size_t  n   = std::min(sa.size(), sb.size());
        for(size_t i=0;i<n;++i){
            char32_t  ca  = sa[i];
            char32_t  cb  = sb[i];
            
            int64_t n   = (int64_t) to_lower(ca) - (int64_t) to_lower(cb);
            if(n<0)
                return Compare::LESSER;
            else if(n>0)
                return Compare::GREATER;
        }
        if(sa.size() < sb.size())
            return Compare::LESSER;
        if(sb.size() < sa.size())
            return Compare::GREATER;
        return Compare::EQUAL;
    }

    std::u32string concat(std::u32string_view a, std::u32string_view b)
    {
        std::u32string ret;
        ret.reserve(a.size()+b.size()+1);
        ret = a;
        ret += b;
        return ret;
    }

    bool    contains(const char32_t* haystack, size_t nHaystack, const char32_t* needle, size_t nNeedle)
    {
        return strnstr(haystack, nHaystack, needle, nNeedle) ? true : false;
    }

    bool    contains(std::u32string_view haystack, std::u32string_view needle)
    {
        return contains(haystack.data(), haystack.size(), needle.data(), needle.size());
    }

    bool    contains_igCase(const char32_t* haystack, size_t nHaystack, const char32_t* needle, size_t nNeedle)
    {
        return strnstr_igCase(haystack, nHaystack, needle, nNeedle) ? true : false;
    }

    bool    contains_igCase(std::u32string_view haystack, std::u32string_view needle)
    {
        return contains_igCase(haystack.data(), haystack.size(), needle.data(), needle.size());
    }

    u32string_set_t        copy(const u32string_view_set_t&input)
    {
        u32string_set_t    ret;
        for(auto& s : input)
            ret.insert(copy(s));
        return ret;
    }

    std::vector<std::u32string>    copy(const std::vector<std::u32string>&input)
    {
        std::vector<std::u32string>    ret;
        ret.reserve(input.size());
        for(const std::u32string& s : input)
            ret.push_back(s);
        return ret;
    }
    
    std::vector<std::u32string>    copy(const std::vector<std::u32string_view>&input)
    {
        std::vector<std::u32string>    ret;
        ret.reserve(input.size());
        for(std::u32string_view s : input)
            ret.push_back(std::u32string(s));
        return ret;
    }

    std::vector<std::u32string>  copy(std::initializer_list<std::u32string_view> input)
    {
        std::vector<std::u32string>    ret;
        ret.reserve(input.size());
        for(std::u32string_view s : input)
            ret.push_back(std::u32string(s));
        return ret;
    }

    size_t  count_characters(const char32_t* s, size_t n)
    {
        return n;
    }
    
    size_t  count_characters(std::u32string_view s)
    {
        return count_characters(s.data(), s.size());
    }
    
    size_t  count_characters(const char32_t* s, size_t n, char32_t ch)
    {
        size_t ret =0;
        if(s && n){
            for(size_t i=0;i<n;++i)
                if(s[i] == ch)
                    ++ret;
        }
        return ret;
    }
    
    size_t  count_characters(std::u32string_view s, char32_t ch)
    {
        return count_characters(s.data(), s.size(), ch);
    }
    

    size_t  count_characters_igCase(const char32_t* s, size_t n, char32_t ch)
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
    

    size_t  count_characters_igCase(std::u32string_view s, char32_t ch)
    {
        return count_characters_igCase(s.data(), s.size(), ch);
    }
    
    size_t  count_start_spaces(std::u32string_view a)
    {
        size_t  ret   = 0;
        for(char32_t ch : a){
            if(is_space(ch)){
                ++ret;
            } else 
                break;
        }
        return ret;
    }

    
    size_t  count_starts(std::u32string_view s, char32_t ch)
    {
        size_t  n = 0;
        for(; (n<s.size()) && (s[n] == ch); ++n)
            ;
        return n;
    }

    bool    ends(std::u32string_view hay, std::u32string_view pat)
    {
        if(pat.size() > hay.size())
            return false;
        return hay.substr(hay.size()-pat.size()) == pat;
    }

    char32_t  first_non_blank_char(std::u32string_view a)
    {
        for(char32_t ch : a){
            if(!is_space(ch))
                return ch;
        }
        return U'\0';
    }

    std::u32string_view  first_non_empty(std::u32string_view a, std::u32string_view b)
    {
        return a.empty() ? b : a;
    }

    std::u32string_view  first_non_empty(std::u32string_view a, std::u32string_view b, std::u32string_view c)
    {
        if(!a.empty())
            return a;
        if(!b.empty())
            return b;
        return c;
    }

    std::u32string_view  first_non_empty(std::u32string_view a, std::u32string_view b, std::u32string_view c, std::u32string_view d)
    {
        if(!a.empty())
            return a;
        if(!b.empty())
            return b;
        if(!c.empty())
            return c;
        return d;
    }

    std::u32string_view  first_non_empty(std::initializer_list<std::u32string_view> args)
    {
        for(std::u32string_view s : args)
            if(!s.empty())
                return s;
        return std::u32string_view();
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


    bool  is_equal(std::u32string_view a, std::u32string_view b)
    {
        return is_equal(compare(a,b));
    }

    bool  is_greater_igCase(std::u32string_view a, std::u32string_view b)
    {
        return is_greater(compare_igCase(a,b));
    }

    bool  is_in(std::u32string_view str, std::u32string_view pat)
    {
        return is_similar(str, pat);
    }
    

    bool  is_in(std::u32string_view str, std::initializer_list<std::u32string_view> pat)
    {
        for(auto& s : pat)
            if(is_similar(str, s))
                return true;
        return false;
    }
    
    bool  is_in(std::u32string_view str, const u32string_view_set_t& pat)
    {
        return pat.contains(str);
    }

    bool  is_in(std::u32string_view str, const std::vector<std::u32string_view>& pat)
    {
        for(auto& s : pat)
            if(is_similar(str, s))
                return true;
        return false;
    }

    bool is_in(char32_t ch, std::u32string_view pat)
    {
        for(char32_t c : pat){
            if(is_similar(c, ch))
                return true;
        }
        return false;
    }

    bool  is_less_igCase(std::u32string_view a, std::u32string_view b)
    {
        return is_less( compare_igCase(a,b));
    }

    bool  is_similar(char32_t a, char32_t b)
    {
        return to_lower(a) == to_lower(b);
    }

    bool  is_similar(std::u32string_view a, std::u32string_view b)
    {
        if(a.size() != b.size())
            return false;
        return is_equal( compare_igCase(a, b));
    }


    bool        matches_at(std::u32string_view haystack, size_t pos, std::u32string_view pattern)
    {
        return starts(haystack.substr(pos), pattern);
    }
    
    bool        matches_at_igCase(std::u32string_view haystack, size_t pos, std::u32string_view pattern)
    {
        return starts_igCase(haystack.substr(pos), pattern);
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

    std::u32string&    set_if_empty(std::u32string&a, std::u32string_view b, bool fOverride)
    {
        if((a.empty() || fOverride) && !b.empty())
            a  = b;
        return a;
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
    
    Expect<bool>  to_boolean(const char32_t*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s, n);
        if(!n)
            return errors::empty_string();
        switch(*s){
        case '0':
            if(is_same(s,n,U"0"))
                return false;
            break;
        case '1':
            if(is_same(s, n, U"1"))
                return true;
            break;
        case 'y':
        case 'Y':
            if(n == 1)
                return true;
            if(is_same(s, n, U"yes"))
                return true;
            break;
        case 'n':
        case 'N':
            if(n == 1)
                return false;
            if(is_same(s, n, U"no"))
                return false;
            break;
        case 't':
        case 'T':
            if(n == 1)
                return true;
            if(is_same(s, n, U"true"))
                return true;
            break;
        case 'f':
        case 'F':
            if(n==1)
                return false;
            if(is_same(s, n, U"false"))
                return false;
            break;
        default:
            break;
        }
        
        return errors::bad_argument();
    }

    Expect<bool> to_boolean(std::u32string_view s)
    {
        return to_boolean(s.data(), s.size());
    }

    Expect<double>  to_double(const char32_t*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        return to_double(to_string(std::u32string_view(s,n)));

        #if 0
        trim_ws(s, n);
        switch(n){
        case 0:
            return 0.;
        case 3:
            if(strncasecmp(s, U"nan", 3) == 0)
                return NaN;
            if(strncasecmp(s, U"inf", 3) == 0)
                return INF;
            break;
        }
        

        double  result = NaN;
        auto [p,ec] = std::from_chars(s, s+n, result, std::chars_format::general);
        if(ec != std::errc())
            return std::unexpected(std::make_error_code(ec));
        return result;
        #endif
    }

    Expect<double>  to_double(std::u32string_view s)
    {
        return to_double(s.data(), s.size());
    }

    Expect<float>  to_float(const char32_t*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        return to_float(to_string(std::u32string_view(s,n)));

        #if 0
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
        auto [p,ec] = std::from_char32_ts(s, s+n, result, std::char32_ts_format::general);
        if(ec != std::errc())
            return std::unexpected(std::make_error_code(ec));
        return result;
        #endif
    }

    Expect<float>  to_float(std::u32string_view s)
    {
        return to_float(s.data(), s.size());
    }



    std::u32string_view  to_u32string_view(const std::u8string_view&s)
    {
        return std::u32string_view((const char32_t*) s.data(), s.size());
    }



    u32string_view_set_t  to_u32string_view_set(const u32string_set_t& vals)
    {
        u32string_view_set_t  ret;
        for(const std::u32string& v : vals)
            ret.insert(v);
        return ret;
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

namespace std {
    ostream& operator<<(ostream& out, u32string_view sv)
    {
        for(char32_t ch : sv)
            out << yq::to_string_view(ch);
        return out;
    }

    ostream& operator<<(ostream& out, const u32string& s)
    {
        return out << (u32string_view) s;
    }
}
