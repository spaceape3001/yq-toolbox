////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/basic/preamble.hpp>

namespace yq::global {
    namespace function {
    
        //! FIRST function of name
        const MethodInfo*                       info(std::string_view);
        
        //! ALL infos to all functions
        const std::vector<const MethodInfo*>&   infos();

        //! ALL infos of named functions
        std::vector<const MethodInfo*>          infos(std::string_view);
        
        //! Invokes the specified name
        Expect<Any> invoke(std::string_view);
        Expect<Any> invoke(std::string_view, const std::vector<Any>&);
        Expect<Any> invoke(std::string_view, std::initializer_list<Any>);

        //! ALL function names
        const string_view_set_t&        names();
    }

    namespace variable {

        //! Gets the variable (as Any)
        Expect<Any>                     get(std::string_view);
    
        //! ALL variable names
        const string_view_set_t&        names();
        
        //! Gets the variable information
        const PropertyInfo*             info(std::string_view);

        //! Information to ALL variables
        const std::vector<const PropertyInfo*>& infos();

        //! Sets the variable
        std::error_code                 set(std::string_view, const Any&);

        //! Sets the variable
        std::error_code                 set(std::string_view, std::string_view);
    }
}
