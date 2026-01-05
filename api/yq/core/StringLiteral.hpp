////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

// using example
// https://pureprogrammer.org/wp/2021/12/19/using-string-literals-as-c-template-parameters/

#include <algorithm>
#include <string_view>

namespace yq {

    /*! \brief String literal (for template parameters)
    
    
        Little gem for allowing templates based on string, thus you can do
        
        template <StringLiteral Name> void print();
        print<"Hello World!">();
        
        Or use with classes, wherever you need to capture a string.
    */
    template <size_t N>
    struct StringLiteral {
        char value[N+1];

        //! Constructs (from program string)
        constexpr StringLiteral(const char (&str)[N])
        {
            std::copy_n(str, N, value);
            value[N] = '\0';
        }
        
        //! Gets the value as a string view
        constexpr std::string_view view() const  noexcept
        {
            return std::string_view(value, N);
        }
        
        //! Gets the value as a C-style string pointer
        constexpr const char* c_str() const 
        {
            return value;
        }
    };
}
