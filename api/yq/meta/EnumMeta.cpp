////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "EnumMeta.hpp"
#include <yq/errors.hpp>
#include <yq/core/Expect.hpp>
#include <yq/core/StreamOps.hpp>

namespace yq::meta_impl {
    void    format_enum(Stream&str, const EnumDef&ei, int v)
    {
        std::string_view txt    = ei.key_of(v);
        if(txt.empty()){
            str << v;
        } else {
            str << txt;
        }
    }
    
    int_x   parse_enum(const EnumDef&ei, std::string_view txt)
    {
        if(txt.empty())
            return ei.default_value();
        return ei.value_of(txt);
    }
}
