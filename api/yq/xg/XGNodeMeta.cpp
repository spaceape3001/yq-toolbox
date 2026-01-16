////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "XGNodeMeta.hpp"
#include "XGDocNode.hpp"
#include <yq/meta/Init.hpp>
#include <yq/vector/Vector2.hpp>

YQ_TYPE_IMPLEMENT(yq::XGNodeMeta)

namespace yq {

    bool        XGNodeMeta::operator==(const XGNodeMeta&) const = default;
    
    XGDocNode       XGNodeMeta::spawn() const
    {
        XGDocNode   ret;
        ret.bgcolor         = bgcolor;
        ret.color           = color;
        ret.label           = label;
        ret.node_type       = node_type;
        ret.position        = ZERO;
        ret.size            = ONE;
        ret.spec_data       = spec_data;
        ret.spec_type       = spec_type;
        return ret;
    }

    static void reg_node_meta()
    {
        auto w = writer<XGNodeMeta>();
        w.description("Executive Graph Node Meta");
    }
    
    YQ_INVOKE(reg_node_meta();)
}
