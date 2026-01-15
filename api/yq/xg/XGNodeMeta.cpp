////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "XGNodeMeta.hpp"
#include <yq/meta/Init.hpp>

YQ_TYPE_IMPLEMENT(yq::XGNodeMeta)

namespace yq {
    XGNodeMeta::XGNodeMeta() = default;
    XGNodeMeta::XGNodeMeta(const XGNodeMeta&) = default;
    XGNodeMeta::XGNodeMeta(XGNodeMeta&&) = default;
    XGNodeMeta::~XGNodeMeta() = default;
    XGNodeMeta& XGNodeMeta::operator=(const XGNodeMeta&) = default;
    XGNodeMeta& XGNodeMeta::operator=(XGNodeMeta&&) = default;
    bool        XGNodeMeta::operator==(const XGNodeMeta&) const = default;
    
    static void reg_node_meta()
    {
        auto w = writer<XGNodeMeta>();
        w.description("Executive Graph Node Meta");
    }
    
    YQ_INVOKE(reg_node_meta();)
}
