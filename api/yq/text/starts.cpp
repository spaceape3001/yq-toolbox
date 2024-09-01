////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/text/starts.hpp>
#include <yq/text/chars.hpp>
#include <string>

namespace yq {
    bool    any_starts(const std::vector<std::string>&haystack, std::string_view pat)
    {
        for(auto& s : haystack)
            if(starts(s, pat))
                return true;
        return false;
    }
    
    bool    any_starts(const std::vector<std::string_view>&haystack, std::string_view pat)
    {
        for(auto& s : haystack)
            if(starts(s, pat))
                return true;
        return false;
    }
    
    bool    any_starts(const std::initializer_list<std::string_view>&haystack, std::string_view pat)
    {
        for(auto& s : haystack)
            if(starts(s, pat))
                return true;
        return false;
    }
    
    bool    any_starts_igCase(const std::vector<std::string>&haystack, std::string_view pat)
    {
        for(auto& s : haystack)
            if(starts_igCase(s, pat))
                return true;
        return false;
    }
    
    bool    any_starts_igCase(const std::vector<std::string_view>&haystack, std::string_view pat)
    {
        for(auto& s : haystack)
            if(starts_igCase(s, pat))
                return true;
        return false;
    }
    
    bool    any_starts_igCase(std::initializer_list<std::string_view> haystack, std::string_view pat)
    {
        for(auto& s : haystack)
            if(starts_igCase(s, pat))
                return true;
        return false;
    }
    
    bool  starts(const char* s, size_t n, const char* pat, size_t nPat)
    {
        if(s && n && pat && (nPat<=n)){
            for(size_t i=0;i<nPat;++i)
                if(s[i] != pat[i])
                    return false;
            return true;
        }
        
        return false;
    }
    
    bool  starts(std::string_view s, std::string_view pat)
    {
        return starts(s.data(), s.size(), pat.data(), pat.size());
    }
    
    bool  starts_igCase(const char* s, size_t n, const char* pat, size_t nPath)
    {
        if(s && n && pat && (nPath<=n)){
            for(size_t i=0;i<nPath;++i)
                if(to_lower(s[i]) != to_lower(pat[i]))
                    return false;
            return true;
        }
        
        return false;
    }
    
    bool  starts_igCase(std::string_view s, std::string_view pat)
    {
        return starts_igCase(s.data(), s.size(), pat.data(), pat.size());
    }

}
