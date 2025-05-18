////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "AlgebraString.hpp"
#include <yq/core/StreamOps.hpp>
#include <yq/meta/Init.hpp>

YQ_TYPE_IMPLEMENT(yq::AlgebraString)

using namespace yq;

namespace {
    void    print_algebraString(Stream& str, const AlgebraString& v)
    {
        str << v.algebra;
    }
    
    static std::string_view write_algebraString(const AlgebraString& v)
    {
        return v.algebra;
    }

    static bool parse_algebraString(AlgebraString& v, std::string_view str)
    {
        v.algebra   = std::string(str);
        return true;
    }
    
    static std::string  convert_algebraString_to_string(const AlgebraString&v)
    {
        return v.algebra;
    }
    
    static AlgebraString    convert_string_to_algebra(const std::string&v )
    {
        return { v };
    }
    
    static void reg_algString()
    {
        {
            auto w = writer<AlgebraString>();
            w.description("User algrebra expression");
            w.converts<std::string, convert_algebraString_to_string>();
            w.print<print_algebraString>();
            w.format<write_algebraString>();
            w.parse<parse_algebraString>();
        }
        
        {
            auto w = writer<std::string>();
            w.converts<AlgebraString, convert_string_to_algebra>();
        }
    }
    
    YQ_INVOKE(reg_algString();)
}
