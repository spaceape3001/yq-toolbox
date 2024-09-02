////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/basic/KV.hpp>
#include <yq/typedef/string_maps.hpp>

namespace yq {

    /*! \brief Method, URI, Version triple
    */
    struct MethodUriVersion {
        std::string_view    method, uri, version;
        bool    operator==(const MethodUriVersion&) const = default;
    };

    //! Parses all parameters from a URL query string
    StringViewMultiMap      parse_parameters(std::string_view);
    
    //! Parses the method/uri/version from the appropriate http intro declaration
    MethodUriVersion        parse_method_uri(std::string_view);

    //! Parses an HTTP header line into key/value
    KVView                  parse_header_line(std::string_view);
    
    //! Parses the HTTP cookie line
    StringViewMultiMap      parse_cookie(std::string_view);
    
    //! Return result for stripped query, the value and the rest of the line
    struct QueryStripped {
        std::string     value;
        std::string     rest;
    };

    /*! \brief Gets the specified query and returns the non-matching parameters
    
        Finds the given query string & removes it from the query.
        
        \param[in] key      Key being searched for
        \param[in] query    The query string
        \param[in] first    TRUE to take the first occurance of key found, FALSE to take the last
    */
    QueryStripped           stripped_query(std::string_view key, std::string_view query, bool first=false);
    
}
