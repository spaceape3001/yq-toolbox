////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "XGSpecType.hpp"
#include <yq/meta/Init.hpp>
#include <yq/core/Enumeration.hxx>

YQ_ENUM_IMPLEMENT(yq::XGSpecType)
YQ_TYPE_IMPLEMENT(yq::XGSpecType)

namespace yq {
    static void reg_spectype()
    {
        auto w = writer<XGSpecType>();
        w.description("Executive Graph Specification Type");
    }
    
    YQ_INVOKE(reg_spectype();)
}
