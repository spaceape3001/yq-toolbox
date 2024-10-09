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
#include <yq/typedef/string_sets.hpp>

namespace yq {

    /*! \brief Copies the u32string
    
        This doesn't return a reference, but actually makes a copy.
    */
    inline std::u32string  copy(std::u32string_view s)
    {
        return std::u32string(s);
    }
    
    u32string_set_t        copy(const u32string_view_set_t&);

    /*! \brief Copies the vector of u32string
    
        This doesn't return a reference, but actually makes a copy.
    */
    std::vector<std::u32string>  copy(const std::vector<std::u32string>&);

    /*! \brief Copies the vector of u32string-views
    
        This doesn't return a reference, but actually makes a copy.
    */
    std::vector<std::u32string>  copy(const std::vector<std::u32string_view>&);
    
    std::vector<std::u32string>  copy(std::initializer_list<std::u32string_view>);
}
