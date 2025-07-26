////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Algebra.hpp"
#include <yq/core/StreamOps.hpp>
#include <yq/meta/Init.hpp>

YQ_TYPE_IMPLEMENT(yq::Algebra)

using namespace yq;

namespace {
    void    print_algebraString(Stream& str, const Algebra& v)
    {
        str << v.algebra;
    }
    
    static std::string_view write_algebraString(const Algebra& v)
    {
        return v.algebra;
    }

    static bool parse_algebraString(Algebra& v, std::string_view str)
    {
        v.algebra   = std::string(str);
        return true;
    }
    
    static std::string  convert_algebraString_to_string(const Algebra&v)
    {
        return v.algebra;
    }
    
    static Algebra    convert_string_to_algebra(const std::string&v )
    {
        return { v };
    }
    
    static void reg_algString()
    {
        {
            auto w = writer<Algebra>();
            w.description("User algrebra expression");
            w.converts<std::string, convert_algebraString_to_string>();
            w.print<print_algebraString>();
            w.format<write_algebraString>();
            w.parse<parse_algebraString>();
        }
        
        {
            auto w = writer<std::string>();
            w.converts<Algebra, convert_string_to_algebra>();
        }
    }
    
    YQ_INVOKE(reg_algString();)
}
