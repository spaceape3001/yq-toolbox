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
        
        template <typename S>
        S&        write_stream(S& s) const
        {
            return s << protocol << '/' << major << '.' << minor;
        }
    };
    
    inline consteval VersionSpec    http09() { return { "HTTP", 0, 9 }; }
    inline consteval VersionSpec    http10() { return { "HTTP", 1, 0 }; }
    inline consteval VersionSpec    http11() { return { "HTTP", 1, 1 }; }
    
    bool                    is_similar(const VersionSpec& a, const VersionSpec& b);
    VersionSpec             to_version_spec(std::string_view);
    VersionSpec             to_version_spec(const char*, size_t);
    
    class Stream;
    
    namespace mithril {
        class WebHtml;
    }

    Stream& operator<<(Stream&, const VersionSpec&);
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const VersionSpec&);
    
    template <typename S>
    requires (!std::is_same_v<S, mithril::WebHtml>)
    S&  operator<<(S& s, const VersionSpec&v)
    {
        return v.write_stream(s);
    }
}
