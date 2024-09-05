////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <initializer_list>
#include <string>
#include <string_view>
#include <vector>
#include <yq-toolbox/typedef/string_sets.hpp>

namespace yq {

    /*! \brief Copies the string
    
        This doesn't return a reference, but actually makes a copy.
    */
    inline std::string  copy(std::string_view s)
    {
        return std::string(s);
    }
    
    string_set_t        copy(const string_view_set_t&);

    /*! \brief Copies the vector of string
    
        This doesn't return a reference, but actually makes a copy.
    */
    std::vector<std::string>  copy(const std::vector<std::string>&);

    /*! \brief Copies the vector of string-views
    
        This doesn't return a reference, but actually makes a copy.
    */
    std::vector<std::string>  copy(const std::vector<std::string_view>&);
    
    std::vector<std::string>  copy(std::initializer_list<std::string_view>);
}
