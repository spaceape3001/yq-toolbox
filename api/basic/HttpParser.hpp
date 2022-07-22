////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/preamble.hpp>
#include <basic/KV.hpp>

namespace yq {

    struct MethodUriVersion {
        std::string_view    method, uri, version;
        bool    operator==(const MethodUriVersion&) const = default;
    };

    StringViewMultiMap      parse_parameters(std::string_view);
    MethodUriVersion        parse_method_uri(std::string_view);

    KVView                  parse_header_line(std::string_view);
    StringViewMultiMap      parse_cookie(std::string_view);
    
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
