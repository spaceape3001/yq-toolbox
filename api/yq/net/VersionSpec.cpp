////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "VersionSpec.hpp"
#include <yq/core/Logging.hpp>
#include <yq/core/StreamOps.hpp>
#include <yq/text/basic.hpp>
#include <yq/text/chars.hpp>
#include <yq/text/match.hpp>

namespace yq {
    Stream& operator<<(Stream&s, const VersionSpec&v)
    {
        return v.write_stream(s);
    }
    
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&s, const VersionSpec&v)
    {
        return v.write_stream(s);
    }

    bool       is_similar(const VersionSpec& a, const VersionSpec& b)
    {
        return is_similar(a.protocol, b.protocol) && (a.major == b.major) && (a.minor == b.minor);
    }
    
    VersionSpec         to_version_spec(const char* s0, size_t cb)
    {
        VersionSpec     ret;
        if(!s0 || !cb)
            return ret;
        
        enum Mode {
            Major = 0,
            Dot,
            Minor,
            Done
        };
        
        const char* y   = strnchr(s0, cb, '/');
        if(!y){
            ret.protocol    = std::string_view(s0, cb);
        } else {
            ret.protocol    = std::string_view(s0, y);
            ++y;
            Mode        mode    = Major;
            for(const char* z = y; z<(s0+cb); ++z){
                char ch = *z;
                switch(mode){
                case Major:
                    if(is_digit(ch)){
                        ret.major = ret.major + (uint16_t) (ch - '0');
                    } else if(ch == '.'){
                        mode    = Dot;
                    } else
                        mode    = Done;
                    break;
                case Dot:
                    if(!is_digit(ch)){
                        mode    = Done;
                        break;
                    } 
                    mode    = Minor;
                    ret.minor = (uint16_t) (ch - '0');
                    break;
                case Minor:
                    if(!is_digit(ch)){
                        mode    = Done;
                    } else {
                        ret.minor = ret.minor + (uint16_t) (ch - '0');
                    }
                    break;
                default:
                    break;
                }
            }
        }
        
        return ret;
    }

    VersionSpec             to_version_spec(std::string_view s)
    {
        return to_version_spec(s.data(), s.size());
    }
}
