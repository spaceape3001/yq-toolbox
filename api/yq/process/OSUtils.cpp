////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "OSUtils.hpp"
#include <format>

namespace yq::os {
    std::string     expected_shared_library_name(std::string_view cmakeTarget)
    {
        #if defined(__unix__)
            #ifdef NDEBUG
                return std::format("lib{}.so", cmakeTarget);
            #else
                return std::format("lib{}D.so", cmakeTarget);
            #endif
        #elif defined(WIN32)
            #ifdef NDEBUG
                return std::format("{}.DLL", cmakeTarget);
            #else
                return std::format("{}D.DLL", cmakeTarget);
            #endif
        #else
            //  TODO (add in other OS... later)
            return std::string(cmakeTarget);
        #endif
    }
}
