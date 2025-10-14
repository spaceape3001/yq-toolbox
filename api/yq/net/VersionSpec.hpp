////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Version.hpp>
#include <string_view>

namespace log4cpp { class CategoryStream; }

namespace yq {

    //! Structure for version specification as in Protocol/Major.Minor
    struct VersionSpec {
    
        //! Protocol (ie, HTTP)
        std::string_view    protocol;
        
        //! Major version
        uint16_t            major = 0;
        
        //! Minor version
        uint16_t            minor = 0;
        
        //! Implicit operator to the version
        operator Version() const { return Version { major, minor, 0, 0 }; }
        
        //! Equality operator
        bool    operator==(const VersionSpec&) const = default;
        
        //! Writes the version spec to a formatting stream (ie, std ostream, a log, etc)
        template <typename S>
        S&        write_stream(S& s) const
        {
            return s << protocol << '/' << major << '.' << minor;
        }
    };
    
    //! Constant for HTTP/0.9
    inline consteval VersionSpec    http09() { return { "HTTP", 0, 9 }; }

    //! Constant for HTTP/1.0
    inline consteval VersionSpec    http10() { return { "HTTP", 1, 0 }; }

    //! Constant for HTTP/1.1
    inline consteval VersionSpec    http11() { return { "HTTP", 1, 1 }; }
    
    //! Compares two version specs for case insensitive "similarness" (ie, http vs HTTP will return true)
    bool                    is_similar(const VersionSpec& a, const VersionSpec& b);
    
    //! Parses the string to make a version spec
    //! \note The string needs to stay alive
    VersionSpec             to_version_spec(std::string_view);

    //! Parses the string to make a version spec
    //! \note The string needs to stay alive
    VersionSpec             to_version_spec(const char*, size_t);
    
    class Stream;
    
    namespace mithril {
        class WebHtml;
    }

    //! Streams a version spec to our stream
    //! (Needed as the generic streamer doesn't seem to work)
    Stream& operator<<(Stream&, const VersionSpec&);
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const VersionSpec&);
    
    template <typename S>
    requires (!std::is_same_v<S, mithril::WebHtml>)
    S&  operator<<(S& s, const VersionSpec&v)
    {
        return v.write_stream(s);
    }
}
